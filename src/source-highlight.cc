/*
 * Copyright (C) 1999-2008  Lorenzo Bettini <http://www.lorenzobettini.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>
#include <iostream>
#include <exception>
#include <boost/shared_ptr.hpp>

#include "sourcehighlight.h"

#include "cmdline.h"
#include "copyright.h"
#include "reportbugs.h"
#include "fileutil.h"
#include "verbose.h"
#include "langmap.h"
#include "languageinfer.h"
#include "utils.h"
#include "highlightbuilderexception.h"
#include "parserexception.h"
#include "debuglistener.h"
#include "ctagsmanager.h"
#include "stopwatch.h"
#include "lineranges.h"

using namespace std;

/**
 * how language inference should be made: NOINFERENCE = no inference at all,
 * INFERFIRST = inference has priority (e.g., if --infer-lang is specified),
 * INFERATLAST = try inference as the last chance
 */
enum InferPolicy {
    NOINFERENCE = 0, INFERFIRST, INFERATLAST
};

static void print_copyright();
static void print_reportbugs();
static void print_version();
static string inferLang(const string &inputFileName);
static string getMappedLang(const string &s, LangMap &langmap);
static void printError(const string &s);
static void print_cgi_header();

/**
 * Exits for a generic error (i.e., file not found)
 */
static void exitError(const string &s);

static string getLangFileName(InferPolicy infer, const string &inputFileName,
        const string &langFileName, const string &langName, LangMap &langMap);

static bool verbose = false;
static bool failsafe = false;

#ifdef BUILD_AS_CGI
#include "envmapper.h"
#endif // BUILD_AS_CGI
/**
 * Print progress status information (provided --quiet is not specified)
 * @param message
 */
#define PROGRESSINFO(message) if (!args_info.quiet_given) cerr << message;

int main(int argc, char * argv[]) {
    gengetopt_args_info args_info; // command line structure
    bool is_cgi = false;

#ifdef BUILD_AS_CGI
    // map environment to parameters if used as CGI
    char **temp_argv;
    temp_argv = map_environment(&argc, argv);
    is_cgi = temp_argv != argv;
    argv = temp_argv;
#endif // BUILD_AS_CGI
    if (cmdline_parser(argc, argv, &args_info) != 0) {
        // calls cmdline parser. The user gived bag args if it doesn't return -1
        return EXIT_FAILURE;
    }

    if (args_info.version_given) {
        print_version();
        print_copyright();
        cmdline_parser_free(&args_info);
        return EXIT_SUCCESS;
    }

    if (args_info.help_given || args_info.detailed_help_given) {
        cout << "GNU ";
        if (args_info.detailed_help_given) {
            cmdline_parser_print_detailed_help();
        } else {
            cmdline_parser_print_help();
        }
        print_reportbugs();
        cmdline_parser_free(&args_info);
        return EXIT_SUCCESS;
    }

    // set possible line ranges
    boost::shared_ptr<LineRanges> lineRanges;
    if (args_info.line_range_given) {
        lineRanges = boost::shared_ptr<LineRanges>(new LineRanges);
        for (unsigned int i = 0; i < args_info.line_range_given; ++i) {
            if (lineRanges->addRange(args_info.line_range_arg[i]) != NO_ERROR) {
                string invalid_range = args_info.line_range_arg[i];
                cmdline_parser_free(&args_info);
                exitError("invalid line range: " + invalid_range);
            }
        }
    }

    if (args_info.range_context_given) {
        if (!args_info.line_range_given) {
            cmdline_parser_free(&args_info);
            exitError(
                    "option --range-context makes sense only when a range is specified");
        }

        lineRanges->setContextLines(args_info.range_context_arg);
    }

    // if a stopwatch is created, when it is deleted (automatically
    // since we're using a shared pointer, it will print the
    // elapsed seconds.
    boost::shared_ptr<StopWatch> stopwatch;
    if (args_info.statistics_given) {
        stopwatch = boost::shared_ptr<StopWatch>(new StopWatch);
    }

    verbose = args_info.verbose_given;
    failsafe = args_info.failsafe_given;

    string inputFile;
    string outputFile;
    string srcLang;
    string outputFormat;
    string langFile;
    string outLangFile;
    string dataDir;
    string outputDir;

    set_file_util_verbose(verbose);

    if (args_info.input_given)
        inputFile = args_info.input_arg;

    if (args_info.output_given)
        outputFile = args_info.output_arg;

    // for cgi force output to standard output
    if (is_cgi)
        outputFile = "STDOUT";

    if (args_info.src_lang_given)
        srcLang = args_info.src_lang_arg;

    if (args_info.lang_def_given)
        langFile = args_info.lang_def_arg;

    if (args_info.outlang_def_given)
        outLangFile = args_info.outlang_def_arg;

    // the default for output format is html
    outputFormat = args_info.out_format_arg;

    if (args_info.data_dir_given) {
        dataDir = args_info.data_dir_arg;
    }

    if (args_info.output_dir_given) {
        outputDir = args_info.output_dir_arg;
    }

    /*
     the starting default path to search for files is computed at
     run-time: it is
     the path of the binary + ".." + RELATIVEDATADIR
     this should make the package relocable (i.e., not stuck
     with a fixed installation directory).
     Of course, the GNU standards for installation directories
     should be followed, but this is not a problem if you use
     configure and make install features.
     If no path is specified in the running program we go back to
     the absolute datadir.
     */
    // this is defined in fileutil.cc
    string prefix_dir = get_file_path(argv[0]);
    if (prefix_dir.size())
        start_path = get_file_path(argv[0]) + RELATIVEDATADIR;
    else
        start_path = ABSOLUTEDATADIR;

    try {
        // initialize map files
        LangMap langmap(dataDir, args_info.lang_map_arg);

        // just print the input language list and associations
        if (args_info.lang_list_given) {
            langmap.open();
            langmap.print();
            return (EXIT_SUCCESS);
        }

        LangMap outlangmap(dataDir, args_info.outlang_map_arg);

        // just print the input language list and associations
        if (args_info.outlang_list_given) {
            outlangmap.open();
            outlangmap.print();
            return (EXIT_SUCCESS);
        }

        string cssUrl;
        if (args_info.css_given)
            cssUrl = args_info.css_arg;

        string docTitle;
        if (args_info.title_given)
            docTitle = args_info.title_arg;

        if (args_info.check_lang_given || args_info.check_outlang_given
                || args_info.show_regex_given
                || args_info.show_lang_elements_given
                || args_info.lang_list_given || args_info.outlang_list_given) {
            // FIXME just a bogus outlang file specification not to search in outlang.map
            outLangFile = "html.outlang";
        }

        // initialize the main source highlight object
        SourceHighlight sourcehighlight(getLangFileName(NOINFERENCE,
                outputFile, outLangFile, outputFormat
                        + (cssUrl.size() ? +"-css" : ""), outlangmap));

        // and sets all its properties according to the command line args
        sourcehighlight.setDataDir(dataDir);

        boost::shared_ptr<DebugListener> debugListener;

        // if a simple check is required...
        if (args_info.check_lang_given) {
            cout << "checking " << args_info.check_lang_arg << "... ";
            sourcehighlight.checkLangDef(args_info.check_lang_arg);
            // if we're here, everything went fine!
            cout << "OK" << endl;
            // otherwise an exception has already been thrown
            return (EXIT_SUCCESS);
        }

        if (args_info.check_outlang_given) {
            cout << "checking " << args_info.check_outlang_arg << "... ";
            sourcehighlight.checkOutLangDef(args_info.check_outlang_arg);
            // if we're here, everything went fine!
            cout << "OK" << endl;
            // otherwise an exception has already been thrown
            return (EXIT_SUCCESS);
        }

        // just print the highlightstate if show-regex is specified
        if (args_info.show_regex_given) {
            sourcehighlight.printHighlightState(args_info.show_regex_arg, cout);
            return (EXIT_SUCCESS);
        }

        // just print the lang elems if show-lang-elements is specified
        if (args_info.show_lang_elements_given) {
            sourcehighlight.printLangElems(args_info.show_lang_elements_arg,
                    cout);
            return (EXIT_SUCCESS);
        }

        sourcehighlight.setGenerateEntireDoc((!args_info.no_doc_given)
                && (args_info.doc_given || (docTitle.size()) || cssUrl.size()));
        sourcehighlight.setStyleDefaultFile(args_info.style_defaults_arg);
        sourcehighlight.setStyleFile(args_info.style_file_arg);
        if (args_info.style_css_file_given)
            sourcehighlight.setStyleCssFile(args_info.style_css_file_arg);
        sourcehighlight.setGenerateVersion(args_info.gen_version_flag != 0);
        sourcehighlight.setCss(cssUrl);
        sourcehighlight.setTitle(docTitle);
        sourcehighlight.setOutputDir(outputDir);
        sourcehighlight.setLineRanges(lineRanges.get());

        if (args_info.debug_langdef_given) {
            debugListener = boost::shared_ptr<DebugListener>(new DebugListener);
            const string debugType = args_info.debug_langdef_arg;
            if (debugType == "interactive")
                debugListener->setInteractive(true);
            sourcehighlight.setHighlightEventListener(debugListener.get());
            // during debugging disable optimizations
            sourcehighlight.setOptimize(false);
        }

        if (args_info.header_given)
            sourcehighlight.setHeaderFileName(args_info.header_arg);

        if (args_info.footer_given)
            sourcehighlight.setFooterFileName(args_info.footer_arg);

        bool generateLineNumbers = args_info.line_number_given
                || args_info.line_number_ref_given;
        sourcehighlight.setGenerateLineNumbers(generateLineNumbers);

        if (args_info.line_number_given) {
            // set the line number padding char (default is always '0')
            sourcehighlight.setLineNumberPad(args_info.line_number_arg[0]);
        }

        if (args_info.line_number_ref_given) {
            sourcehighlight.setGenerateLineNumberRefs(true);
            sourcehighlight.setLineNumberAnchorPrefix(
                    args_info.line_number_ref_arg);
        }

        if (generateLineNumbers) {
            // when generating line numbers tabs must be translated
            // otherwise the output line will not be aligned
            // due to the presence of line numbers
            sourcehighlight.setTabSpaces(8);
        }

        // whether to give precedence to language inference
        InferPolicy inferPolicy = (args_info.infer_lang_given ? INFERFIRST
                : INFERATLAST);

        RefPosition refposition;
        string gen_references_arg = args_info.gen_references_arg;
        if (gen_references_arg == "inline")
            refposition = INLINE;
        else if (gen_references_arg == "postline")
            refposition = POSTLINE;
        else if (gen_references_arg == "postdoc")
            refposition = POSTDOC;

        boost::shared_ptr<CTagsManager> ctagsManager;
        if (args_info.gen_references_given) {
            string ctags = args_info.ctags_arg;
            string ctags_file = args_info.ctags_file_arg;

            // build the additional arguments for the ctags command
            if (args_info.gen_references_given && ctags != "") {
                if (inputFile.size()) {
                    ctags += " ";
                    ctags += inputFile;
                } else if (args_info.inputs_num) {
                    for (unsigned int i = 0; i < (args_info.inputs_num); ++i) {
                        ctags += " ";
                        ctags += args_info.inputs[i];
                    }
                }
            }

            // the ctags command must be executed if --ctags is specified with an empty string
            ctagsManager
                    = boost::shared_ptr<CTagsManager>(
                            new CTagsManager(ctags_file, ctags, ctags != "", refposition));
            sourcehighlight.setCTagsManager(ctagsManager.get());
        }

        if (args_info.range_separator_given) {
            if (!args_info.line_range_given) {
                cmdline_parser_free(&args_info);
                exitError(
                        "option --range-separator makes sense only when a range is specified");
            }

            sourcehighlight.setRangeSeparator(args_info.range_separator_arg);
        }

        // OK, let's highlight!

        // for cgi we can only process one file specified with --input
        if (args_info.inputs_num && !is_cgi) {
            // the output file name is empty, but we don't want to generate to stdout
            sourcehighlight.setCanUseStdOut(false);
            // in case multiple input files were specified (without --input)
            for (unsigned int i = 0; i < (args_info.inputs_num); ++i) {
                PROGRESSINFO(string("Processing ")+ args_info.inputs[i] + " ... ");
                sourcehighlight.highlight(args_info.inputs[i], "",
                        getLangFileName(inferPolicy, args_info.inputs[i],
                                langFile, srcLang, langmap));
                PROGRESSINFO("created " + sourcehighlight.createOutputFileName(args_info.inputs[i]) + "\n");
            }
        } else {
            if (is_cgi)
                print_cgi_header();

            // in case only one input file was specified with --input
            sourcehighlight.highlight(inputFile, outputFile, getLangFileName(
                    inferPolicy, inputFile, langFile, srcLang, langmap));
        }
    } catch (const HighlightBuilderException &e) {
        cerr << e << endl;
        exit(EXIT_FAILURE);
    } catch (const ParserException &e) {
        cerr << e << endl;
        exit(EXIT_FAILURE);
    } catch (const exception &e) {
        exitError(e.what());
    }

    cmdline_parser_free(&args_info);

    return 0;
}

void print_copyright() {
    int i;

    for (i = 1; i <= copyright_text_length; ++i)
        cout << copyright_text[i] << endl;;
}

void print_reportbugs() {
    int i;

    for (i = 1; i <= reportbugs_text_length; ++i)
        cout << reportbugs_text[i] << endl;
}

void print_version() {
    cout << "GNU " << PACKAGE << " " << VERSION << endl;
}

string inferLang(const string &inputFileName) {
    VERBOSELN("inferring input language...");
    if (!inputFileName.size()) {
        printError("missing feature: language inference requires input file");
        return "";
    }

    LanguageInfer languageInfer;

    const string &result = languageInfer.infer(inputFileName);
    if (result.size()) {
        VERBOSELN("inferred input language: " + result);
    } else {
        VERBOSELN("couldn't infer input language");
    }

    return result;
}

string getMappedLang(const string &s, LangMap &langmap) {
    // make sure the lang map file is open
    langmap.open();

    // OK now map it into a .lang file
    string mapped_lang = langmap.get_file(s);

    if (!mapped_lang.size()) {
        // try the lower version
        mapped_lang = langmap.get_file(Utils::tolower(s));
    }

    return mapped_lang;
}

string getLangFileName(InferPolicy infer, const string &inputFileName,
        const string &langFileName, const string &langName, LangMap &langMap) {
    string langFile;

    // language inference has the precedence
    if (infer == INFERFIRST) {
        langFile = inferLang(inputFileName);
        langFile = getMappedLang(langFile, langMap);
        if (langFile.size())
            return langFile;
    }

    // then if a lang file name was specified we're done
    if (langFileName.size())
        return langFileName;

    // now try with the langName
    langFile = getMappedLang(langName, langMap);
    if (langFile.size())
        return langFile;

    // otherwise try with the inputFileName file extension
    langFile = getMappedLang(get_file_extension(inputFileName), langMap);
    if (langFile.size())
        return langFile;

    // OK, as a last chance let's try with language infer
    if (infer == INFERATLAST) {
        langFile = getMappedLang(inferLang(inputFileName), langMap);
        if (langFile.size())
            return langFile;
    }

    // if we're here we failed all checks
    // if failsafe is specified we default to default.lang
    if (failsafe)
        langFile = "default.lang";

    if (!langFile.size()) {
        // if we're here we must exit with failure
        if (langName.size())
            exitError("could not find a language definition for " + langName);
        else
            exitError("could not find a language definition for input file "
                    + inputFileName);
    }

    return langFile;
}

void printError(const string &s) {
    cerr << PACKAGE << ": " << s << endl;
}

void exitError(const string &s) {
    printError(s);
    exit(EXIT_FAILURE);
}

void print_cgi_header() {
    cout << "Content-type: text/html\n";
    cout << "\n";
}

