/*	$NetBSD: readline.h,v 1.34 2013/05/28 00:10:34 christos Exp $	*/

/*-
 * Copyright (c) 1997 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jaromir Dolecek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _READLINE_H_
#define _READLINE_H_

#include <sys/types.h>
#include <stdio.h>

#ifndef EXPORT_API
#define EXPORT_API
#endif // EXPORT_API


/* list of readline stuff supported by editline library's readline wrapper */

/* typedefs */
typedef int	  Function(const char *, int);
typedef void	  VFunction(void);
typedef void	  VCPFunction(char *);
typedef char	 *CPFunction(const char *, int);
typedef char	**CPPFunction(const char *, int, int);
typedef char     *rl_compentry_func_t(const char *, int);
typedef int	  rl_command_func_t(int, int);

/* only supports length */
typedef struct {
	int length;
} HISTORY_STATE;

typedef void *histdata_t;

typedef struct _hist_entry {
	const char	*line;
	histdata_t 	 data;
} HIST_ENTRY;

typedef struct _keymap_entry {
	char type;
#define ISFUNC	0
#define ISKMAP	1
#define ISMACR	2
	Function *function;
} KEYMAP_ENTRY;

#define KEYMAP_SIZE	256

typedef KEYMAP_ENTRY KEYMAP_ENTRY_ARRAY[KEYMAP_SIZE];
typedef KEYMAP_ENTRY *Keymap;

#define control_character_threshold	0x20
#define control_character_bit		0x40

#ifndef CTRL
#include <sys/ioctl.h>
#if !defined(__sun) && !defined(__hpux) && !defined(_AIX)
#include <sys/ttydefaults.h>
#endif
#ifndef CTRL
#define CTRL(c)		((c) & 037)
#endif
#endif
#ifndef UNCTRL
#define UNCTRL(c)	(((c) - 'a' + 'A')|control_character_bit)
#endif

#define RUBOUT		0x7f
#define ABORT_CHAR	CTRL('G')
#define RL_READLINE_VERSION 	0x0402
#define RL_PROMPT_START_IGNORE	'\1'
#define RL_PROMPT_END_IGNORE	'\2'

/* global variables used by readline enabled applications */
#ifdef __cplusplus
extern "C" {
#endif
EXPORT_API extern const char	*rl_library_version;
EXPORT_API extern int 		rl_readline_version; 
EXPORT_API extern char		*rl_readline_name;
EXPORT_API extern FILE		*rl_instream;
EXPORT_API extern FILE		*rl_outstream;
EXPORT_API extern char		*rl_line_buffer;
EXPORT_API EXPORT_API extern int		 rl_point, rl_end;
EXPORT_API EXPORT_API extern int		 history_base, history_length;
EXPORT_API extern int		 max_input_history;
EXPORT_API extern char		*rl_basic_word_break_characters;
EXPORT_API extern char		*rl_completer_word_break_characters;
EXPORT_API extern char		*rl_completer_quote_characters;
EXPORT_API extern Function		*rl_completion_entry_function;
EXPORT_API extern char		*(*rl_completion_word_break_hook)(void);
EXPORT_API extern CPPFunction	*rl_attempted_completion_function;
EXPORT_API extern int		 rl_attempted_completion_over;
EXPORT_API extern int		rl_completion_type;
EXPORT_API extern int		rl_completion_query_items;
EXPORT_API extern char		*rl_special_prefixes;
EXPORT_API extern int		rl_completion_append_character;
EXPORT_API extern int		rl_inhibit_completion;
EXPORT_API extern Function		*rl_pre_input_hook;
EXPORT_API extern Function		*rl_startup_hook;
EXPORT_API extern char		*rl_terminal_name;
EXPORT_API extern int		rl_already_prompted;
EXPORT_API extern char		*rl_prompt;
/*
 * The following is not implemented
 */
EXPORT_API extern int		rl_catch_signals;
EXPORT_API extern int		rl_catch_sigwinch;
EXPORT_API EXPORT_API EXPORT_API extern KEYMAP_ENTRY_ARRAY emacs_standard_keymap,
			emacs_meta_keymap,
			emacs_ctlx_keymap;
EXPORT_API extern int		rl_filename_completion_desired;
EXPORT_API extern int		rl_ignore_completion_duplicates;
EXPORT_API extern int		(*rl_getc_function)(FILE *);
EXPORT_API extern VFunction	*rl_redisplay_function;
EXPORT_API extern VFunction	*rl_completion_display_matches_hook;
EXPORT_API extern VFunction	*rl_prep_term_function;
EXPORT_API extern VFunction	*rl_deprep_term_function;
EXPORT_API extern int		readline_echoing_p;
EXPORT_API extern int		_rl_print_completions_horizontally;

/* supported functions */
EXPORT_API char		*readline(const char *);
EXPORT_API int		 rl_initialize(void);

EXPORT_API void		 using_history(void);
EXPORT_API int		 add_history(const char *);
EXPORT_API void		 clear_history(void);
EXPORT_API void		 stifle_history(int);
EXPORT_API int		 unstifle_history(void);
EXPORT_API int		 history_is_stifled(void);
EXPORT_API int		 where_history(void);
EXPORT_API HIST_ENTRY	*current_history(void);
EXPORT_API HIST_ENTRY	*history_get(int);
EXPORT_API HIST_ENTRY	*remove_history(int);
EXPORT_API HIST_ENTRY	*replace_history_entry(int, const char *, histdata_t);
EXPORT_API int		 history_total_bytes(void);
EXPORT_API int		 history_set_pos(int);
EXPORT_API HIST_ENTRY	*previous_history(void);
EXPORT_API HIST_ENTRY	*next_history(void);
EXPORT_API int		 history_search(const char *, int);
EXPORT_API int		 history_search_prefix(const char *, int);
EXPORT_API int		 history_search_pos(const char *, int, int);
EXPORT_API int		 read_history(const char *);
EXPORT_API int		 write_history(const char *);
EXPORT_API int		 history_truncate_file (const char *, int);
EXPORT_API int		 history_expand(char *, char **);
EXPORT_API char	       **history_tokenize(const char *);
EXPORT_API const char	*get_history_event(const char *, int *, int);
EXPORT_API char		*history_arg_extract(int, int, const char *);

EXPORT_API char		*tilde_expand(char *);
EXPORT_API char		*filename_completion_function(const char *, int);
EXPORT_API char		*username_completion_function(const char *, int);
EXPORT_API int		 rl_complete(int, int);
EXPORT_API int		 rl_read_key(void);
EXPORT_API char	       **completion_matches(const char *, CPFunction *);
EXPORT_API void		 rl_display_match_list(char **, int, int);

EXPORT_API int		 rl_insert(int, int);
EXPORT_API int		 rl_insert_text(const char *);
EXPORT_API void		 rl_reset_terminal(const char *);
EXPORT_API int		 rl_bind_key(int, rl_command_func_t *);
EXPORT_API int		 rl_newline(int, int);
EXPORT_API void		 rl_callback_read_char(void);
EXPORT_API void		 rl_callback_handler_install(const char *, VCPFunction *);
EXPORT_API void		 rl_callback_handler_remove(void);
EXPORT_API void		 rl_redisplay(void);
EXPORT_API int		 rl_get_previous_history(int, int);
EXPORT_API void		 rl_prep_terminal(int);
EXPORT_API void		 rl_deprep_terminal(void);
EXPORT_API int		 rl_read_init_file(const char *);
EXPORT_API int		 rl_parse_and_bind(const char *);
EXPORT_API int		 rl_variable_bind(const char *, const char *);
EXPORT_API void		 rl_stuff_char(int);
EXPORT_API int		 rl_add_defun(const char *, Function *, int);
EXPORT_API HISTORY_STATE	*history_get_history_state(void);
EXPORT_API void		 rl_get_screen_size(int *, int *);
EXPORT_API void		 rl_set_screen_size(int, int);
EXPORT_API char 		*rl_filename_completion_function (const char *, int);
EXPORT_API int		 _rl_abort_internal(void);
EXPORT_API int		 _rl_qsort_string_compare(char **, char **);
EXPORT_API char 	       **rl_completion_matches(const char *, rl_compentry_func_t *);
EXPORT_API void		 rl_forced_update_display(void);
EXPORT_API int		 rl_set_prompt(const char *);
EXPORT_API int		 rl_on_new_line(void);

/*
 * The following are not implemented
 */
EXPORT_API int		 rl_kill_text(int, int);
EXPORT_API Keymap		 rl_get_keymap(void);
EXPORT_API void		 rl_set_keymap(Keymap);
EXPORT_API Keymap		 rl_make_bare_keymap(void);
EXPORT_API int		 rl_generic_bind(int, const char *, const char *, Keymap);
EXPORT_API int		 rl_bind_key_in_map(int, rl_command_func_t *, Keymap);
EXPORT_API void		 rl_cleanup_after_signal(void);
EXPORT_API void		 rl_free_line_state(void);
#ifdef __cplusplus
}
#endif

#endif /* _READLINE_H_ */
