/** @file cmdline.h
 *  @brief The header file for the command line option parser
 *  generated by GNU Gengetopt version 2.22.1
 *  http://www.gnu.org/software/gengetopt.
 *  DO NOT modify this file, since it can be overwritten
 *  @author GNU Gengetopt by Lorenzo Bettini */

#ifndef CMDLINE_H
#define CMDLINE_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* for FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef CMDLINE_PARSER_PACKAGE
/** @brief the program name */
#define CMDLINE_PARSER_PACKAGE PACKAGE
#endif

#ifndef CMDLINE_PARSER_VERSION
/** @brief the program version */
#define CMDLINE_PARSER_VERSION VERSION
#endif

/** @brief Where the command line options are stored */
struct gengetopt_args_info
{
  const char *help_help; /**< @brief Print help and exit help description.  */
  const char *detailed_help_help; /**< @brief Print help, including all details and hidden options, and exit help description.  */
  const char *version_help; /**< @brief Print version and exit help description.  */
  char * input_arg;	/**< @brief input file. default std input.  */
  char * input_orig;	/**< @brief input file. default std input original value given at command line.  */
  const char *input_help; /**< @brief input file. default std input help description.  */
  char * output_arg;	/**< @brief output file. default std output. If STDOUT is specified, the output is directed to standard output.  */
  char * output_orig;	/**< @brief output file. default std output. If STDOUT is specified, the output is directed to standard output original value given at command line.  */
  const char *output_help; /**< @brief output file. default std output. If STDOUT is specified, the output is directed to standard output help description.  */
  char * src_lang_arg;	/**< @brief source language (use --lang-list to get the complete list).  If not specified, the source language will be guessed from the file extension..  */
  char * src_lang_orig;	/**< @brief source language (use --lang-list to get the complete list).  If not specified, the source language will be guessed from the file extension. original value given at command line.  */
  const char *src_lang_help; /**< @brief source language (use --lang-list to get the complete list).  If not specified, the source language will be guessed from the file extension. help description.  */
  const char *lang_list_help; /**< @brief list all the supported language and associated language definition file help description.  */
  const char *outlang_list_help; /**< @brief list all the supported output language and associated language definition file help description.  */
  char * out_format_arg;	/**< @brief output format (use --outlang-list to get the complete list) (default='html').  */
  char * out_format_orig;	/**< @brief output format (use --outlang-list to get the complete list) original value given at command line.  */
  const char *out_format_help; /**< @brief output format (use --outlang-list to get the complete list) help description.  */
  const char *doc_help; /**< @brief create an output file that can be used as a stand alone document (e.g., not to be included in another one) help description.  */
  const char *no_doc_help; /**< @brief cancel the --doc option even if it is implied (e.g., when css is given) help description.  */
  char * css_arg;	/**< @brief the external style sheet filename.  Implies --doc.  */
  char * css_orig;	/**< @brief the external style sheet filename.  Implies --doc original value given at command line.  */
  const char *css_help; /**< @brief the external style sheet filename.  Implies --doc help description.  */
  char * title_arg;	/**< @brief give a title to the output document.  Implies --doc.  */
  char * title_orig;	/**< @brief give a title to the output document.  Implies --doc original value given at command line.  */
  const char *title_help; /**< @brief give a title to the output document.  Implies --doc help description.  */
  int tab_arg;	/**< @brief specify tab length. (default='8').  */
  char * tab_orig;	/**< @brief specify tab length. original value given at command line.  */
  const char *tab_help; /**< @brief specify tab length. help description.  */
  char * header_arg;	/**< @brief file to insert as header.  */
  char * header_orig;	/**< @brief file to insert as header original value given at command line.  */
  const char *header_help; /**< @brief file to insert as header help description.  */
  char * footer_arg;	/**< @brief file to insert as footer.  */
  char * footer_orig;	/**< @brief file to insert as footer original value given at command line.  */
  const char *footer_help; /**< @brief file to insert as footer help description.  */
  char * style_file_arg;	/**< @brief specify the file containing format options (default='default.style').  */
  char * style_file_orig;	/**< @brief specify the file containing format options original value given at command line.  */
  const char *style_file_help; /**< @brief specify the file containing format options help description.  */
  char * style_css_file_arg;	/**< @brief specify the file containing format options (in css syntax).  */
  char * style_css_file_orig;	/**< @brief specify the file containing format options (in css syntax) original value given at command line.  */
  const char *style_css_file_help; /**< @brief specify the file containing format options (in css syntax) help description.  */
  char * style_defaults_arg;	/**< @brief specify the file containing defaults for format options (default='style.defaults').  */
  char * style_defaults_orig;	/**< @brief specify the file containing defaults for format options original value given at command line.  */
  const char *style_defaults_help; /**< @brief specify the file containing defaults for format options help description.  */
  char * outlang_def_arg;	/**< @brief output language definition file.  */
  char * outlang_def_orig;	/**< @brief output language definition file original value given at command line.  */
  const char *outlang_def_help; /**< @brief output language definition file help description.  */
  char * outlang_map_arg;	/**< @brief output language map file (default='outlang.map').  */
  char * outlang_map_orig;	/**< @brief output language map file original value given at command line.  */
  const char *outlang_map_help; /**< @brief output language map file help description.  */
  char * data_dir_arg;	/**< @brief directory where language definition files and language maps are searched for.  If not specified these files are searched for in the current directory and in the data dir installation directory.  */
  char * data_dir_orig;	/**< @brief directory where language definition files and language maps are searched for.  If not specified these files are searched for in the current directory and in the data dir installation directory original value given at command line.  */
  const char *data_dir_help; /**< @brief directory where language definition files and language maps are searched for.  If not specified these files are searched for in the current directory and in the data dir installation directory help description.  */
  char * output_dir_arg;	/**< @brief output directory.  */
  char * output_dir_orig;	/**< @brief output directory original value given at command line.  */
  const char *output_dir_help; /**< @brief output directory help description.  */
  char * lang_def_arg;	/**< @brief language definition file.  */
  char * lang_def_orig;	/**< @brief language definition file original value given at command line.  */
  const char *lang_def_help; /**< @brief language definition file help description.  */
  char * lang_map_arg;	/**< @brief language map file (default='lang.map').  */
  char * lang_map_orig;	/**< @brief language map file original value given at command line.  */
  const char *lang_map_help; /**< @brief language map file help description.  */
  char * show_lang_elements_arg;	/**< @brief prints the language elements that are defined in the language definition file.  */
  char * show_lang_elements_orig;	/**< @brief prints the language elements that are defined in the language definition file original value given at command line.  */
  const char *show_lang_elements_help; /**< @brief prints the language elements that are defined in the language definition file help description.  */
  const char *infer_lang_help; /**< @brief force to infer source script language (overriding given language specification) help description.  */
  char * line_number_arg;	/**< @brief number all output lines, using the specified padding character (default='0').  */
  char * line_number_orig;	/**< @brief number all output lines, using the specified padding character original value given at command line.  */
  const char *line_number_help; /**< @brief number all output lines, using the specified padding character help description.  */
  char * line_number_ref_arg;	/**< @brief number all output lines and generate an anchor, made of the specified prefix + the line number (default='line').  */
  char * line_number_ref_orig;	/**< @brief number all output lines and generate an anchor, made of the specified prefix + the line number original value given at command line.  */
  const char *line_number_ref_help; /**< @brief number all output lines and generate an anchor, made of the specified prefix + the line number help description.  */
  char ** line_range_arg;	/**< @brief generate only the lines in the specified range(s).  */
  char ** line_range_orig;	/**< @brief generate only the lines in the specified range(s) original value given at command line.  */
  unsigned int line_range_min; /**< @brief generate only the lines in the specified range(s)'s minimum occurreces */
  unsigned int line_range_max; /**< @brief generate only the lines in the specified range(s)'s maximum occurreces */
  const char *line_range_help; /**< @brief generate only the lines in the specified range(s) help description.  */
  char * range_separator_arg;	/**< @brief the optional separator to be printed among ranges (e.g., \"...\").  */
  char * range_separator_orig;	/**< @brief the optional separator to be printed among ranges (e.g., \"...\") original value given at command line.  */
  const char *range_separator_help; /**< @brief the optional separator to be printed among ranges (e.g., \"...\") help description.  */
  int range_context_arg;	/**< @brief number of (context) lines generated even if not in range.  */
  char * range_context_orig;	/**< @brief number of (context) lines generated even if not in range original value given at command line.  */
  const char *range_context_help; /**< @brief number of (context) lines generated even if not in range help description.  */
  char * gen_references_arg;	/**< @brief generate references (default='inline').  */
  char * gen_references_orig;	/**< @brief generate references original value given at command line.  */
  const char *gen_references_help; /**< @brief generate references help description.  */
  char * ctags_file_arg;	/**< @brief specify the file generated by ctags that will be used to generate references (default='tags').  */
  char * ctags_file_orig;	/**< @brief specify the file generated by ctags that will be used to generate references original value given at command line.  */
  const char *ctags_file_help; /**< @brief specify the file generated by ctags that will be used to generate references help description.  */
  char * ctags_arg;	/**< @brief how to run the ctags command.  If this option is not specified, ctags will be executed with the default value.  If it is specified with an empty string, ctags will not be executed at all (default='ctags --excmd=n --tag-relative=yes').  */
  char * ctags_orig;	/**< @brief how to run the ctags command.  If this option is not specified, ctags will be executed with the default value.  If it is specified with an empty string, ctags will not be executed at all original value given at command line.  */
  const char *ctags_help; /**< @brief how to run the ctags command.  If this option is not specified, ctags will be executed with the default value.  If it is specified with an empty string, ctags will not be executed at all help description.  */
  const char *verbose_help; /**< @brief verbose mode on help description.  */
  const char *quiet_help; /**< @brief print no progress information help description.  */
  const char *statistics_help; /**< @brief print some statistics (i.e., elapsed time) help description.  */
  int gen_version_flag;	/**< @brief put source-highlight version in the generated file (default=on).  */
  const char *gen_version_help; /**< @brief put source-highlight version in the generated file help description.  */
  char * check_lang_arg;	/**< @brief only check the correctness of a language definition file.  */
  char * check_lang_orig;	/**< @brief only check the correctness of a language definition file original value given at command line.  */
  const char *check_lang_help; /**< @brief only check the correctness of a language definition file help description.  */
  char * check_outlang_arg;	/**< @brief only check the correctness of an output language definition file.  */
  char * check_outlang_orig;	/**< @brief only check the correctness of an output language definition file original value given at command line.  */
  const char *check_outlang_help; /**< @brief only check the correctness of an output language definition file help description.  */
  const char *failsafe_help; /**< @brief if no language definition is found for the input, it is simply copied to the output help description.  */
  char * debug_langdef_arg;	/**< @brief debug a language definition.  In dump mode just dumps all the steps; in interactive, at each step, waits for some input (press ENTER to step) (default='dump').  */
  char * debug_langdef_orig;	/**< @brief debug a language definition.  In dump mode just dumps all the steps; in interactive, at each step, waits for some input (press ENTER to step) original value given at command line.  */
  const char *debug_langdef_help; /**< @brief debug a language definition.  In dump mode just dumps all the steps; in interactive, at each step, waits for some input (press ENTER to step) help description.  */
  char * show_regex_arg;	/**< @brief show the regular expression automaton corresponding to a language definition file.  */
  char * show_regex_orig;	/**< @brief show the regular expression automaton corresponding to a language definition file original value given at command line.  */
  const char *show_regex_help; /**< @brief show the regular expression automaton corresponding to a language definition file help description.  */
  
  unsigned int help_given ;	/**< @brief Whether help was given.  */
  unsigned int detailed_help_given ;	/**< @brief Whether detailed-help was given.  */
  unsigned int version_given ;	/**< @brief Whether version was given.  */
  unsigned int input_given ;	/**< @brief Whether input was given.  */
  unsigned int output_given ;	/**< @brief Whether output was given.  */
  unsigned int src_lang_given ;	/**< @brief Whether src-lang was given.  */
  unsigned int lang_list_given ;	/**< @brief Whether lang-list was given.  */
  unsigned int outlang_list_given ;	/**< @brief Whether outlang-list was given.  */
  unsigned int out_format_given ;	/**< @brief Whether out-format was given.  */
  unsigned int doc_given ;	/**< @brief Whether doc was given.  */
  unsigned int no_doc_given ;	/**< @brief Whether no-doc was given.  */
  unsigned int css_given ;	/**< @brief Whether css was given.  */
  unsigned int title_given ;	/**< @brief Whether title was given.  */
  unsigned int tab_given ;	/**< @brief Whether tab was given.  */
  unsigned int header_given ;	/**< @brief Whether header was given.  */
  unsigned int footer_given ;	/**< @brief Whether footer was given.  */
  unsigned int style_file_given ;	/**< @brief Whether style-file was given.  */
  unsigned int style_css_file_given ;	/**< @brief Whether style-css-file was given.  */
  unsigned int style_defaults_given ;	/**< @brief Whether style-defaults was given.  */
  unsigned int outlang_def_given ;	/**< @brief Whether outlang-def was given.  */
  unsigned int outlang_map_given ;	/**< @brief Whether outlang-map was given.  */
  unsigned int data_dir_given ;	/**< @brief Whether data-dir was given.  */
  unsigned int output_dir_given ;	/**< @brief Whether output-dir was given.  */
  unsigned int lang_def_given ;	/**< @brief Whether lang-def was given.  */
  unsigned int lang_map_given ;	/**< @brief Whether lang-map was given.  */
  unsigned int show_lang_elements_given ;	/**< @brief Whether show-lang-elements was given.  */
  unsigned int infer_lang_given ;	/**< @brief Whether infer-lang was given.  */
  unsigned int line_number_given ;	/**< @brief Whether line-number was given.  */
  unsigned int line_number_ref_given ;	/**< @brief Whether line-number-ref was given.  */
  unsigned int line_range_given ;	/**< @brief Whether line-range was given.  */
  unsigned int range_separator_given ;	/**< @brief Whether range-separator was given.  */
  unsigned int range_context_given ;	/**< @brief Whether range-context was given.  */
  unsigned int gen_references_given ;	/**< @brief Whether gen-references was given.  */
  unsigned int ctags_file_given ;	/**< @brief Whether ctags-file was given.  */
  unsigned int ctags_given ;	/**< @brief Whether ctags was given.  */
  unsigned int verbose_given ;	/**< @brief Whether verbose was given.  */
  unsigned int quiet_given ;	/**< @brief Whether quiet was given.  */
  unsigned int statistics_given ;	/**< @brief Whether statistics was given.  */
  unsigned int gen_version_given ;	/**< @brief Whether gen-version was given.  */
  unsigned int check_lang_given ;	/**< @brief Whether check-lang was given.  */
  unsigned int check_outlang_given ;	/**< @brief Whether check-outlang was given.  */
  unsigned int failsafe_given ;	/**< @brief Whether failsafe was given.  */
  unsigned int debug_langdef_given ;	/**< @brief Whether debug-langdef was given.  */
  unsigned int show_regex_given ;	/**< @brief Whether show-regex was given.  */

  char **inputs ; /**< @brief unamed options (options without names) */
  unsigned inputs_num ; /**< @brief unamed options number */
} ;

/** @brief The additional parameters to pass to parser functions */
struct cmdline_parser_params
{
  int override; /**< @brief whether to override possibly already present options (default 0) */
  int initialize; /**< @brief whether to initialize the option structure gengetopt_args_info (default 1) */
  int check_required; /**< @brief whether to check that all required options were provided (default 1) */
  int check_ambiguity; /**< @brief whether to check for options already specified in the option structure gengetopt_args_info (default 0) */
  int print_errors; /**< @brief whether getopt_long should print an error message for a bad option (default 1) */
} ;

/** @brief the purpose string of the program */
extern const char *gengetopt_args_info_purpose;
/** @brief the usage string of the program */
extern const char *gengetopt_args_info_usage;
/** @brief all the lines making the help output */
extern const char *gengetopt_args_info_help[];
/** @brief all the lines making the detailed help output (including hidden options and details) */
extern const char *gengetopt_args_info_detailed_help[];

/**
 * The command line parser
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser (int argc, char * const *argv,
  struct gengetopt_args_info *args_info);

/**
 * The command line parser (version with additional parameters - deprecated)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use cmdline_parser_ext() instead
 */
int cmdline_parser2 (int argc, char * const *argv,
  struct gengetopt_args_info *args_info,
  int override, int initialize, int check_required);

/**
 * The command line parser (version with additional parameters)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_ext (int argc, char * const *argv,
  struct gengetopt_args_info *args_info,
  struct cmdline_parser_params *params);

/**
 * Save the contents of the option struct into an already open FILE stream.
 * @param outfile the stream where to dump options
 * @param args_info the option struct to dump
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_dump(FILE *outfile,
  struct gengetopt_args_info *args_info);

/**
 * Save the contents of the option struct into a (text) file.
 * This file can be read by the config file parser (if generated by gengetopt)
 * @param filename the file where to save
 * @param args_info the option struct to save
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_file_save(const char *filename,
  struct gengetopt_args_info *args_info);

/**
 * Print the help
 */
void cmdline_parser_print_help(void);
/**
 * Print the detailed help (including hidden options and details)
 */
void cmdline_parser_print_detailed_help(void);
/**
 * Print the version
 */
void cmdline_parser_print_version(void);

/**
 * Initializes all the fields a cmdline_parser_params structure 
 * to their default values
 * @param params the structure to initialize
 */
void cmdline_parser_params_init(struct cmdline_parser_params *params);

/**
 * Allocates dynamically a cmdline_parser_params structure and initializes
 * all its fields to their default values
 * @return the created and initialized cmdline_parser_params structure
 */
struct cmdline_parser_params *cmdline_parser_params_create(void);

/**
 * Initializes the passed gengetopt_args_info structure's fields
 * (also set default values for options that have a default)
 * @param args_info the structure to initialize
 */
void cmdline_parser_init (struct gengetopt_args_info *args_info);
/**
 * Deallocates the string fields of the gengetopt_args_info structure
 * (but does not deallocate the structure itself)
 * @param args_info the structure to deallocate
 */
void cmdline_parser_free (struct gengetopt_args_info *args_info);

/**
 * Checks that all the required options were specified
 * @param args_info the structure to check
 * @param prog_name the name of the program that will be used to print
 *   possible errors
 * @return
 */
int cmdline_parser_required (struct gengetopt_args_info *args_info,
  const char *prog_name);

extern const char *cmdline_parser_gen_references_values[];  /**< @brief Possible values for gen-references. */
extern const char *cmdline_parser_debug_langdef_values[];  /**< @brief Possible values for debug-langdef. */


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* CMDLINE_H */
