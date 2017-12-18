#ifndef MR_MAINFILE
#define MR_MAINFILE "tests/global-tests.c"
#define DEPTH 5
#include "mr.3.h"
#else

#if MR_STAGE == MR_TYPEDEFS
static char* _mr_file27_name = "tests/global-tests.3.mr";
#endif
#define MR_FILE_NAME _mr_file27_name

/* MR4 compiler tests - Global */

/* IO mocks */

#if MR_STAGE == MR_DECLARATIONS
extern String* mock_print_text;
#elif MR_STAGE == MR_FUNCTIONS
String* mock_print_text = &(String){1024, 0, (char[1024]){0}};
#endif
#if MR_STAGE == MR_DECLARATIONS
extern String* mock_input_file_text;
#elif MR_STAGE == MR_FUNCTIONS
String* mock_input_file_text = &(String){1024, 0, (char[1024]){0}};
#endif
#if MR_STAGE == MR_DECLARATIONS
extern String* mock_output_file_text;
#elif MR_STAGE == MR_FUNCTIONS
String* mock_output_file_text = &(String){8192, 0, (char[8192]){0}};
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Int mock_input_file_index;
#elif MR_STAGE == MR_FUNCTIONS
Int mock_input_file_index = 0;
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Int mock_input_line_reset_index;
#elif MR_STAGE == MR_FUNCTIONS
Int mock_input_line_reset_index = 0;
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Bool mock_print_active;
#elif MR_STAGE == MR_FUNCTIONS
Bool mock_print_active = false;
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Char mock_output_file_last;
#elif MR_STAGE == MR_FUNCTIONS
Char mock_output_file_last = '\0';
#endif

#if MR_STAGE == MR_DECLARATIONS
extern File* input_file;
#elif MR_STAGE == MR_FUNCTIONS
File* input_file = NULL;
#endif
#if MR_STAGE == MR_DECLARATIONS
extern File* actual_output_file;
#elif MR_STAGE == MR_FUNCTIONS
File* actual_output_file = NULL;
#endif
#if MR_STAGE == MR_DECLARATIONS
extern File* expected_output_file;
#elif MR_STAGE == MR_FUNCTIONS
File* expected_output_file = NULL;
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Bool tests_passed;
#elif MR_STAGE == MR_FUNCTIONS
Bool tests_passed = false;
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Bool had_test_error;
#elif MR_STAGE == MR_FUNCTIONS
Bool had_test_error = false;
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode print(String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_print = "print";
#define MR_FUNC_NAME _func_name_print
Returncode print(String* text) {
  if (mock_print_active) {
    CHECK(21, String_concat(mock_print_text, text) )
  }
  else {
    CHECK(23, Sys_print_raw(sys, text) )
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode set_mock_file_text(String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_set_mock_file_text = "set-mock-file-text";
#define MR_FUNC_NAME _func_name_set_mock_file_text
Returncode set_mock_file_text(String* text) {
  CHECK(26, String_copy(mock_input_file_text, text) )
  mock_input_file_index = 0;
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode file_open(String* name, Bool is_read, File** file);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_file_open = "file-open";
#define MR_FUNC_NAME _func_name_file_open
Returncode file_open(String* name, Bool is_read, File** file) {
  /* do nothing */
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode file_close(File* file);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_file_close = "file-close";
#define MR_FUNC_NAME _func_name_file_close
Returncode file_close(File* file) {
  /* do nothing */
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode file_getc(File* file, Char* ch);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_file_getc = "file-getc";
#define MR_FUNC_NAME _func_name_file_getc
Returncode file_getc(File* file, Char* ch) {
  TEST_ASSERT(36, file == glob->input_file)
  if (mock_input_file_index >= mock_input_file_text->length) {
    (*ch) = EOF;
    return OK;
  }
  if ((mock_input_file_index) < 0 || (mock_input_file_index) >= (mock_input_file_text)->length) RAISE(40)
  (*ch) = ((mock_input_file_text)->values[mock_input_file_index]);
  if (mock_input_file_index == mock_input_line_reset_index) {
    glob->line_number = 1;
  }
  mock_input_file_index += 1;
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode file_putc(File* file, Char ch);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_file_putc = "file-putc";
#define MR_FUNC_NAME _func_name_file_putc
Returncode file_putc(File* file, Char ch) {
  TEST_ASSERT(46, file == glob->output_file)
  CHECK(47, String_append(mock_output_file_text, ch) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode file_write(File* file, String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_file_write = "file-write";
#define MR_FUNC_NAME _func_name_file_write
Returncode file_write(File* file, String* text) {
  TEST_ASSERT(50, file == glob->output_file)
  {int n; for (n = (0); n < (text->length); ++n) {
    if ((n) < 0 || (n) >= (text)->length) RAISE(52)
    Char ch = ((text)->values[n]);
    if (ch != '\n' || ch != mock_output_file_last) {
      CHECK(54, String_append(mock_output_file_text, ch) )
    }
    mock_output_file_last = ch;
  }}
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode write_global(String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_write_global = "write-global";
#define MR_FUNC_NAME _func_name_write_global
Returncode write_global(String* text) {
  /* do nothing */
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode write_pre_func(SyntaxTreeFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_write_pre_func = "write-pre-func";
#define MR_FUNC_NAME _func_name_write_pre_func
Returncode write_pre_func(SyntaxTreeFunction* self) {
  /* do nothing */
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode write_post_func();
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_write_post_func = "write-post-func";
#define MR_FUNC_NAME _func_name_write_post_func
Returncode write_post_func() {
  /* do nothing */
  return OK;
}
#undef MR_FUNC_NAME
#endif


#if MR_STAGE == MR_DECLARATIONS
extern String* mock_input_file_name;
#elif MR_STAGE == MR_FUNCTIONS
String* mock_input_file_name = &(String){16, 0, (char[16]){0}};
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode f_setup_test();
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_f_setup_test = "f-setup-test";
#define MR_FUNC_NAME _func_name_f_setup_test
Returncode f_setup_test() {
  free(glob->operator_map);
  free(glob->type_map);
  CHECK(72, Global_init(glob) )
  glob->input_file_name = mock_input_file_name;
  CHECK(74, String_copy(glob->input_file_name, &(String){10, 9, "mock.3.mr"}) )
  glob->line_number = 0;
  glob->save_input = false;
  CHECK(77, String_clear(mock_print_text) )
  CHECK(78, String_clear(mock_input_file_text) )
  CHECK(79, String_clear(mock_output_file_text) )
  mock_output_file_last = '\0';
  mock_input_file_index = 0;
  mock_print_active = false;
  return OK;
}
#undef MR_FUNC_NAME
#endif


/* string assertion */

#if MR_STAGE == MR_DECLARATIONS
Returncode f_assert_string_slice(String* expected, String* actual, Int start, Int slice_length, Bool is_main);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_f_assert_string_slice = "f-assert-string-slice";
#define MR_FUNC_NAME _func_name_f_assert_string_slice
Returncode f_assert_string_slice(String* expected, String* actual, Int start, Int slice_length, Bool is_main) {
  String* actual_slice = &(String){1, 0, ""};
  if (actual->length >= start + slice_length) {
    if ((start) < 0 || (slice_length) < 0 || (start) + (slice_length) > (actual)->length) RAISE(95)
    actual_slice = (&(String){slice_length, slice_length, (actual)->values + (start)});
  }
  else {
    if (actual->length > start) {
      if ((start) < 0 || (actual->length - start) < 0 || (start) + (actual->length - start) > (actual)->length) RAISE(97)
      actual_slice = (&(String){actual->length - start, actual->length - start, (actual)->values + (start)});
    }
  }
  if (is_main) {
    CHECK(99, File_write(actual_output_file, actual_slice) )
    CHECK(100, File_write(actual_output_file, &(String){2, 1, "\n"}) )
  }
  Bool _Bool133;
  CHECK(101, String_equal(actual_slice, expected, &(_Bool133)) )
  if (_Bool133) {
    return OK;
  }
  CHECK(103, Sys_print_raw(sys, &(String){15, 14, "\n  [expected `"}) )
  CHECK(104, Sys_print_raw(sys, expected) )
  CHECK(105, Sys_print_raw(sys, &(String){9, 8, "`, got `"}) )
  CHECK(106, Sys_print_raw(sys, actual_slice) )
  CHECK(107, Sys_print_raw(sys, &(String){4, 3, "`] "}) )
  CHECK(108, write_new_file(&(String){13, 12, "expected.txt"}, expected) )
  CHECK(109, write_new_file(&(String){11, 10, "actual.txt"}, actual_slice) )
  tests_passed = false;
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode write_new_file(String* filename, String* data);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_write_new_file = "write-new-file";
#define MR_FUNC_NAME _func_name_write_new_file
Returncode write_new_file(String* filename, String* data) {
  File* file = NULL;
  CHECK(114, file_open_write(filename, &(file)) )
  CHECK(115, File_write(file, data) )
  CHECK(116, File_close(file) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode f_assert_string(String* expected, String* actual);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_f_assert_string = "f-assert-string";
#define MR_FUNC_NAME _func_name_f_assert_string
Returncode f_assert_string(String* expected, String* actual) {
  TEST_ASSERT(119, NULL != actual)
  CHECK(120, f_assert_string_slice(expected, actual, 0, actual->length, false) )
  return OK;
}
#undef MR_FUNC_NAME
#endif


#if MR_STAGE == MR_DECLARATIONS
Returncode set_test_file_name(String* filename, String* base_name, String* suffix);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_set_test_file_name = "set-test-file-name";
#define MR_FUNC_NAME _func_name_set_test_file_name
Returncode set_test_file_name(String* filename, String* base_name, String* suffix) {
  String* base_dir = &(String){1024, 0, (char[1024]){0}};
  Bool _Bool134;
  CHECK(127, Sys_getenv(sys, &(String){9, 8, "TEST_DIR"}, base_dir, &(_Bool134)) )
  if (_Bool134) {
    CHECK(128, String_copy(filename, base_dir) )
  }
  CHECK(129, String_concat(filename, base_name) )
  CHECK(130, String_concat(filename, suffix) )
  return OK;
}
#undef MR_FUNC_NAME
#endif


#if MR_STAGE == MR_DECLARATIONS
Returncode test_new_file(String* base_name, String* name);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_test_new_file = "test-new-file";
#define MR_FUNC_NAME _func_name_test_new_file
Returncode test_new_file(String* base_name, String* name) {
  String* filename = &(String){256, 0, (char[256]){0}};
  CHECK(135, set_test_file_name(filename, base_name, &(String){6, 5, ".4.mr"}) )
  CHECK(136, file_open_read(filename, &(input_file)) )
  CHECK(137, set_test_file_name(filename, base_name, &(String){12, 11, ".expected.c"}) )
  CHECK(138, file_open_read(filename, &(expected_output_file)) )
  CHECK(139, set_test_file_name(filename, base_name, &(String){10, 9, ".actual.c"}) )
  CHECK(140, file_open_write(filename, &(actual_output_file)) )
  
  had_test_error = false;
  String* line = &(String){1024, 0, (char[1024]){0}};
  Bool _Bool135;
  CHECK(144, read_line(input_file, line, &(String){7, 6, "## @@ "}, &(_Bool135)) )
  if (!_Bool135) {
    CHECK(145, file_error(name, line) )
  }
  Bool _Bool136;
  CHECK(146, read_line(expected_output_file, line, &(String){8, 7, "/// @@ "}, &(_Bool136)) )
  if (!_Bool136) {
    CHECK(147, file_error(name, line) )
  }
  CHECK(148, test_from_file(name) )
  return OK;
}
#undef MR_FUNC_NAME
#endif


#if MR_STAGE == MR_DECLARATIONS
Returncode test_from_file(String* name);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_test_from_file = "test-from-file";
#define MR_FUNC_NAME _func_name_test_from_file
Returncode test_from_file(String* name) {
  String* line = &(String){1024, 0, (char[1024]){0}};
  String* subname = &(String){1024, 0, (char[1024]){0}};
  CHECK(153, String_copy(subname, &(String){6, 5, "start"}))
  if (had_test_error) {
    while (true) {
      Bool _Bool137;
      CHECK(156, read_line(input_file, line, &(String){7, 6, "## @@ "}, &(_Bool137)) )
      if (!(!_Bool137)) break;
    }
    while (true) {
      Bool _Bool138;
      CHECK(158, read_line(expected_output_file, line, &(String){8, 7, "/// @@ "}, &(_Bool138)) )
      if (!(!_Bool138)) break;
    }
  }
  had_test_error = true;
  Bool _Bool139;
  CHECK(160, read_line(input_file, line, NULL, &(_Bool139)) )
  Bool _Bool140;
  CHECK(161, String_equal(line, name, &(_Bool140)) )
  if (!_Bool140) {
    CHECK(162, file_error(name, line) )
  }
  Bool _Bool141;
  CHECK(163, read_line(expected_output_file, line, NULL, &(_Bool141)) )
  Bool _Bool142;
  CHECK(164, String_equal(line, name, &(_Bool142)) )
  if (!_Bool142) {
    CHECK(165, file_error(name, line) )
  }
  CHECK(166, File_write(actual_output_file, &(String){8, 7, "/// @@ "}) )
  CHECK(167, File_write(actual_output_file, name) )
  CHECK(168, File_write(actual_output_file, &(String){2, 1, "\n"}) )
  
  String* input = &(String){4096, 0, (char[4096]){0}};
  String* expected = &(String){4096, 0, (char[4096]){0}};
  Bool _Bool143;
  CHECK(172, read_line(input_file, line, &(String){6, 5, "## @ "}, &(_Bool143)) )
  if (!_Bool143) {
    CHECK(173, file_error(name, line) )
  }
  Bool _Bool144;
  CHECK(174, read_line(expected_output_file, line, &(String){7, 6, "/// @ "}, &(_Bool144)) )
  if (!_Bool144) {
    CHECK(175, file_error(name, line) )
  }
  
  Char type_char = '\0';
  Bool is_error_test = false;
  tests_passed = true;
  while (true) {
    CHECK(181, File_getc(input_file, &(type_char)) )
    is_error_test = type_char == 'e';
    if (is_error_test) {
      CHECK(184, File_getc(input_file, &(type_char)) )
    }
    if (type_char != 'g' && type_char != 'c') {
      CHECK(186, file_error(name, subname) )
    }
    Char _Char145;
    CHECK(187, File_getc(input_file, &(_Char145)) )
    if (_Char145 != ' ') {
      CHECK(188, file_error(name, subname) )
    }
    Bool _Bool146;
    CHECK(189, read_line(input_file, subname, NULL, &(_Bool146)) )
    Bool _Bool147;
    CHECK(190, read_line(expected_output_file, line, NULL, &(_Bool147)) )
    Bool _Bool148;
    CHECK(191, String_equal(line, subname, &(_Bool148)) )
    if (!_Bool148) {
      CHECK(192, file_error(name, subname) )
    }
    CHECK(193, File_write(actual_output_file, &(String){7, 6, "/// @ "}) )
    CHECK(194, File_write(actual_output_file, subname) )
    CHECK(195, File_write(actual_output_file, &(String){2, 1, "\n"}) )
    
    CHECK(197, read_data(input_file, input, &(String){5, 4, "## @"}) )
    CHECK(198, read_data(expected_output_file, expected, &(String){6, 5, "/// @"}) )
    if (type_char == 'c') {
      if (is_error_test) {
        CHECK(201, test_code_error(input, expected) )
      }
      else {
        CHECK(203, test_code(input, expected) )
      }
    }
    else {
      if (is_error_test) {
        CHECK(206, test_global_scope_error(input, expected) )
      }
      else {
        CHECK(208, test_global_scope(input, expected) )
      }
    }
    
    Char _Char149;
    CHECK(210, File_getc(expected_output_file, &(_Char149)) )
    Char _Char150;
    CHECK(211, File_getc(input_file, &(_Char150)) )
    if (!(_Char150 == ' ')) break;
  }
  
  Char _Char151;
  CHECK(213, File_getc(expected_output_file, &(_Char151)) )
  Char _Char152;
  CHECK(214, File_getc(input_file, &(_Char152)) )
  if (_Char152 == EOF) {
    Char _Char153;
    CHECK(215, File_getc(expected_output_file, &(_Char153)) )
    if (_Char153 != EOF) {
      CHECK(216, file_error(name, subname) )
    }
    CHECK(217, File_write(actual_output_file, &(String){7, 6, "/// @\n"}) )
    CHECK(218, File_close(input_file) )
    CHECK(219, File_close(expected_output_file) )
    CHECK(220, File_close(actual_output_file) )
  }
  
  had_test_error = false;
  TEST_ASSERT(223, tests_passed)
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode read_line(File* file, String* line, String* prefix, Bool* found_prefix);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_read_line = "read-line";
#define MR_FUNC_NAME _func_name_read_line
Returncode read_line(File* file, String* line, String* prefix, Bool* found_prefix) {
  CHECK(227, String_clear(line) )
  (*found_prefix) = false;
  Char ch = '\0';
  while (true) {
    CHECK(231, File_getc(file, &(ch)) )
    if (!(ch != EOF && ch != '\n')) break;
    CHECK(233, String_append(line, ch) )
    if (NULL != prefix &&  ! (*found_prefix)) {
      Bool _Bool154;
      CHECK(235, String_equal(line, prefix, &(_Bool154)) )
      if (_Bool154) {
        (*found_prefix) = true;
        return OK;
      }
    }
  }
  if (ch == EOF && line->length == 0) {
    RAISE(239)
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif


#if MR_STAGE == MR_DECLARATIONS
Returncode read_data(File* file, String* data, String* prefix);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_read_data = "read-data";
#define MR_FUNC_NAME _func_name_read_data
Returncode read_data(File* file, String* data, String* prefix) {
  CHECK(243, String_clear(data) )
  String* line = &(String){1024, 0, (char[1024]){0}};
  while (true) {
    Bool _Bool155;
    CHECK(246, read_line(file, line, prefix, &(_Bool155)) )
    if (!(!_Bool155)) break;
    if (data->length > 0) {
      CHECK(248, String_append(data, '\n') )
    }
    CHECK(249, String_concat(data, line) )
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif


#if MR_STAGE == MR_DECLARATIONS
Returncode file_error(String* name, String* subname);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_file_error = "file-error";
#define MR_FUNC_NAME _func_name_file_error
Returncode file_error(String* name, String* subname) {
  CHECK(253, Sys_print_raw(sys, &(String){23, 22, "file format error in ["}) )
  CHECK(254, Sys_print_raw(sys, name) )
  if (NULL != subname) {
    CHECK(256, Sys_print_raw(sys, &(String){6, 5, "] / ["}) )
    CHECK(257, Sys_print_raw(sys, subname) )
  }
  CHECK(258, Sys_print(sys, &(String){2, 1, "]"}) )
  RAISE(259)
}
#undef MR_FUNC_NAME
#endif


/* List tests */
#if MR_STAGE == MR_DECLARATIONS
Returncode test_list();
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_test_list = "test-list";
#define MR_FUNC_NAME _func_name_test_list
Returncode test_list() {
  List* list = &(List){NULL, NULL};
  String* _String156;
  CHECK(265, List_pop(list, (void**)&(_String156)) )
  TEST_ASSERT(265, !(NULL != _String156))
  String* _String157;
  CHECK(266, string_new_copy(&(String){7, 6, "value1"}, &(_String157)) )
  CHECK(266, List_add(list, _String157) )
  String* _String158;
  CHECK(267, string_new_copy(&(String){7, 6, "value2"}, &(_String158)) )
  CHECK(267, List_add(list, _String158) )
  String* _String159;
  CHECK(268, string_new_copy(&(String){7, 6, "value3"}, &(_String159)) )
  CHECK(268, List_add(list, _String159) )
  String* _String160;
  CHECK(269, List_pop(list, (void**)&(_String160)) )
  CHECK(269, f_assert_string(&(String){7, 6, "value1"}, _String160) )
  String* _String161;
  CHECK(270, List_pop(list, (void**)&(_String161)) )
  CHECK(270, f_assert_string(&(String){7, 6, "value2"}, _String161) )
  String* _String162;
  CHECK(271, List_pop(list, (void**)&(_String162)) )
  CHECK(271, f_assert_string(&(String){7, 6, "value3"}, _String162) )
  String* _String163;
  CHECK(272, List_pop(list, (void**)&(_String163)) )
  TEST_ASSERT(272, !(NULL != _String163))
  return OK;
}
#undef MR_FUNC_NAME
#endif


/* NameMap tests */

#if MR_STAGE == MR_DECLARATIONS
Returncode test_name_map();
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_test_name_map = "test-name-map";
#define MR_FUNC_NAME _func_name_test_name_map
Returncode test_name_map() {
  NameMap* map = &(NameMap){NULL, NULL};
  String* _String164;
  CHECK(279, NameMap_find(map, &(String){6, 5, "name1"}, (void**)&(_String164)) )
  TEST_ASSERT(279, !(NULL != _String164))
  CHECK(280, NameMap_add(map, &(String){6, 5, "name1"}, &(String){7, 6, "value1"}) )
  String* _String165;
  CHECK(281, NameMap_find(map, &(String){6, 5, "name1"}, (void**)&(_String165)) )
  CHECK(281, f_assert_string(&(String){7, 6, "value1"}, _String165) )
  String* _String166;
  CHECK(282, NameMap_find(map, &(String){6, 5, "name2"}, (void**)&(_String166)) )
  TEST_ASSERT(282, !(NULL != _String166))
  CHECK(283, NameMap_add(map, &(String){6, 5, "name2"}, &(String){7, 6, "value2"}) )
  String* _String167;
  CHECK(284, NameMap_find(map, &(String){6, 5, "name1"}, (void**)&(_String167)) )
  CHECK(284, f_assert_string(&(String){7, 6, "value1"}, _String167) )
  String* _String168;
  CHECK(285, NameMap_find(map, &(String){6, 5, "name2"}, (void**)&(_String168)) )
  CHECK(285, f_assert_string(&(String){7, 6, "value2"}, _String168) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

#undef MR_FILE_NAME

#ifndef MR_INCLUDES
#define MR_INCLUDES
#include "global/argument.c"
#include "global/common.c"
#include "global/file-io.c"
#include "global/global.c"
#include "global/list.c"
#include "global/map.c"
#include "expression/base-type.c"
#include "expression/call.c"
#include "expression/constant.c"
#include "expression/container.c"
#include "expression/expression.c"
#include "expression/initialize.c"
#include "expression/slice.c"
#include "expression/symbol.c"
#include "syntax-tree/block.c"
#include "syntax-tree/branch.c"
#include "syntax-tree/code.c"
#include "syntax-tree/code-flow.c"
#include "syntax-tree/function.c"
#include "syntax-tree/node.c"
#include "syntax-tree/root.c"
#include "syntax-tree/test.c"
#include "syntax-tree/type.c"
#include "syntax-tree/type-instance.c"
#include "syntax-tree/variable.c"
#include "tests/expression-tests.c"
#include "tests/syntax-tree-tests.c"
#include "mr4-compiler.c"
#if MR_STAGE == MR_TYPES(1)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(2)
#elif MR_STAGE == MR_TYPES(2)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(3)
#elif MR_STAGE == MR_TYPES(3)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(4)
#elif MR_STAGE == MR_TYPES(4)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(5)
#endif
#undef MR_INCLUDES
#endif

#endif