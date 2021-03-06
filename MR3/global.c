static char* _mr_file3_name = "global.2.mr";
#define MR_FILE_NAME _mr_file3_name
/* MR3 compiler - global data */

/* global data object */
String* global_key_word_text = &(String){80, 0, (char[80]){0}};

typedef struct Parsed_key_word Parsed_key_word; struct Parsed_key_word {
  String* text;
  Int spaces;
  Char end;
};

Parsed_key_word* global_key_word = &(Parsed_key_word){0};

typedef struct Global_data Global_data; struct Global_data {
  /* data */
  File* infile;
  File* outfile;
  Array* key_word_map;
  Op_map* op_map;
  Type_map* type_map;
  Var_map* var_map;
  String_list* test_funcs;
  Int max_type_depth;
  /* types */
  Mtype* type_char;
  Mtype* type_bool;
  Mtype* type_int;
  Mtype* type_type;
  Mtype* type_func;
  Mtype* type_string;
  Mtype* type_array;
  Mtype* type_file;
  Mtype* type_sys;
  /* state */
  Parsed_key_word* key_word;
  String* infile_name;
  Int line_num;
  Int spaces;
  St* node;
  Int res_count;
  Mtype* mclass;
  Bool methods;
};
static char* _func_name_Global_data_init_op_map = "Global-data.init-op-map";
#define MR_FUNC_NAME _func_name_Global_data_init_op_map
Returncode Global_data_init_op_map(Global_data* self) {
  Op_map* map = malloc(sizeof(Op_map));
  if (map == NULL) RAISE(44)
  self->op_map = map;
  CHECK(46, Name_map_init(&(map->_base)));
  CHECK(47, Op_map_add(map, &(String){2, 1, "."}, &(String){3, 2, "->"}));
  CHECK(48, Op_map_add(map, &(String){3, 2, ":="}, &(String){2, 1, "="}));
  CHECK(49, Op_map_add_copy(map, &(String){2, 1, "+"}));
  CHECK(50, Op_map_add_copy(map, &(String){2, 1, "-"}));
  CHECK(51, Op_map_add_copy(map, &(String){2, 1, "*"}));
  CHECK(52, Op_map_add_copy(map, &(String){2, 1, "/"}));
  CHECK(53, Op_map_add(map, &(String){2, 1, "="}, &(String){3, 2, "=="}));
  CHECK(54, Op_map_add_copy(map, &(String){3, 2, "!="}));
  CHECK(55, Op_map_add_copy(map, &(String){2, 1, ">"}));
  CHECK(56, Op_map_add_copy(map, &(String){2, 1, "<"}));
  CHECK(57, Op_map_add_copy(map, &(String){3, 2, ">="}));
  CHECK(58, Op_map_add_copy(map, &(String){3, 2, "<="}));
  CHECK(59, Op_map_add(map, &(String){4, 3, "not"}, &(String){2, 1, "!"}));
  CHECK(60, Op_map_add(map, &(String){3, 2, "or"}, &(String){3, 2, "||"}));
  CHECK(61, Op_map_add(map, &(String){4, 3, "and"}, &(String){3, 2, "&&"}));
  CHECK(62, Op_map_add(map, &(String){2, 1, "?"}, &(String){9, 8, "NULL != "}));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Global_data_init_types = "Global-data.init-types";
#define MR_FUNC_NAME _func_name_Global_data_init_types
Returncode Global_data_init_types(Global_data* self) {
  Type_map* map = malloc(sizeof(Type_map));
  if (map == NULL) RAISE(65)
  self->type_map = map;
  CHECK(67, Name_map_init(&(map->_base)));
  CHECK(68, Type_map_add(map, &(String){5, 4, "Char"}, &(self->type_char)));
  CHECK(69, Mtype_set_primitive(self->type_char, &(String){5, 4, "'\\0'"}));
  CHECK(70, Type_map_add(map, &(String){5, 4, "Bool"}, &(self->type_bool)));
  CHECK(71, Mtype_set_primitive(self->type_bool, &(String){6, 5, "false"}));
  CHECK(72, Type_map_add(map, &(String){4, 3, "Int"}, &(self->type_int)));
  CHECK(73, Mtype_set_primitive(self->type_int, &(String){2, 1, "0"}));
  CHECK(74, Type_map_add(map, &(String){5, 4, "Type"}, &(self->type_type)));
  CHECK(75, Mtype_set_primitive(self->type_type, &(String){8, 7, "0, NULL"}));
  CHECK(76, Type_map_add(map, &(String){5, 4, "Func"}, &(self->type_func)));
  CHECK(77, Mtype_set_primitive(self->type_func, &(String){5, 4, "NULL"}));
  CHECK(78, Type_map_add(map, &(String){7, 6, "String"}, &(self->type_string)));
  CHECK(79, Type_map_add(map, &(String){6, 5, "Array"}, &(self->type_array)));
  CHECK(80, Type_map_add(map, &(String){5, 4, "File"}, &(self->type_file)));
  CHECK(81, Type_map_add(map, &(String){4, 3, "Sys"}, &(self->type_sys)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Global_data_init = "Global-data.init";
#define MR_FUNC_NAME _func_name_Global_data_init
Returncode Global_data_init(Global_data* self) {
  self->max_type_depth = 0;
  self->line_num = 0;
  self->methods = false;
  self->res_count = 0;
  global_key_word->text = global_key_word_text;
  self->key_word = NULL;
  CHECK(90, Global_data_init_op_map(self));
  CHECK(91, Global_data_init_types(self));
  CHECK(92, f_init_new_string_list(&(self->test_funcs)));
  return OK;
}
#undef MR_FUNC_NAME

Global_data* glob = &(Global_data){0};


/* read helpers */
static char* _func_name_read_c = "read-c";
#define MR_FUNC_NAME _func_name_read_c
Returncode read_c(Char* ch) {
  CHECK(99, File_getc(glob->infile, &((*ch))));
  if ((*ch) == '\n') {
    glob->line_num = glob->line_num + 1;
  }
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_read_ignore = "read-ignore";
#define MR_FUNC_NAME _func_name_read_ignore
Returncode read_ignore(Int chars) {
  Int n; for (n = 0; n < chars; ++n) {
    Char _Char0;
    CHECK(105, read_c(&(_Char0)));
  }
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_read_cont_spaces = "read-cont-spaces";
#define MR_FUNC_NAME _func_name_read_cont_spaces
Returncode read_cont_spaces() {
  CHECK(108, read_ignore(glob->spaces + 4));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_read_indent = "read-indent";
#define MR_FUNC_NAME _func_name_read_indent
Returncode read_indent(String* ends, Bool indent, String* text, Char* end, Int* spaces) {
  CHECK(111, String_clear(text));
  Char ch = EOF;
  Char q = '\0';
  (*spaces) = 0;
  while (true) {
    /* ignore indent */
    CHECK(117, read_c(&(ch)));
    if (indent) {
      while (true) {
        if (!(ch == ' ')) break;
        (*spaces) = (*spaces) + 1;
        CHECK(122, read_c(&(ch)));
      }
      indent = false;
    }
    if (!(ch != EOF)) break;
    if (q == '\0') {
      if (!(ch != '\n')) break;
      Bool _Bool1;
      CHECK(127, String_has(ends, ch, &(_Bool1)))
      if (!(!_Bool1)) break;
      if (ch == '\'' || ch == '"') {
        q = ch;
      }
    }
    else {
      if (ch == '\\') {
        CHECK(131, String_append(text, ch));
        CHECK(132, read_c(&(ch)));
      }
      else {
        if (ch == q) {
          q = '\0';
        }
      }
    }
    CHECK(135, String_append(text, ch));
  }
  (*end) = ch;
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_read = "read";
#define MR_FUNC_NAME _func_name_read
Returncode read(String* ends, String* text, Char* end) {
  Int _Int2;
  CHECK(139, read_indent(ends, false, text, &((*end)), &(_Int2)));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_read_new = "read-new";
#define MR_FUNC_NAME _func_name_read_new
Returncode read_new(String* ends, String** out_text, Char* end) {
  String* text = &(String){256, 0, (char[256]){0}};
  CHECK(143, read(ends, text, &((*end))));
  CHECK(144, f_new_copy(text, &((*out_text))));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_read_key_word = "read-key-word";
#define MR_FUNC_NAME _func_name_read_key_word
Returncode read_key_word() {
  if (NULL != glob->key_word) {
    return OK;
  }
  glob->key_word = global_key_word;
  CHECK(150, read_indent(&(String){5, 4, " .[("}, true, glob->key_word->text, &(glob->key_word->end), &(glob->key_word->spaces)));
  return OK;
}
#undef MR_FUNC_NAME


/* write helpers */
static char* _func_name_write_c = "write-c";
#define MR_FUNC_NAME _func_name_write_c
Returncode write_c(Char ch) {
  CHECK(155, File_putc(glob->outfile, ch));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write = "write";
#define MR_FUNC_NAME _func_name_write
Returncode write(String* text) {
  CHECK(159, File_write(glob->outfile, text));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write_cstyle = "write-cstyle";
#define MR_FUNC_NAME _func_name_write_cstyle
Returncode write_cstyle(String* text) {
  if (!(NULL != text)) {
    RAISE(164)
  }
  Int index; for (index = 0; index < text->length; ++index) {
    if ((index) < 0 || (index) >= text->length) RAISE(166)
    Char ch = text->chars[index];
    if (ch == '-') {
      CHECK(168, write_c('_'));
    }
    else {
      CHECK(170, write_c(ch));
    }
  }
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write_int = "write-int";
#define MR_FUNC_NAME _func_name_write_int
Returncode write_int(Int num) {
  String* num_str = &(String){64, 0, (char[64]){0}};
  CHECK(174, Int_str(num, num_str));
  CHECK(175, write(num_str));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write_line_num = "write-line-num";
#define MR_FUNC_NAME _func_name_write_line_num
Returncode write_line_num() {
  CHECK(178, write_int(glob->line_num));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write_tb_raise = "write-tb-raise";
#define MR_FUNC_NAME _func_name_write_tb_raise
Returncode write_tb_raise() {
  CHECK(181, write(&(String){7, 6, "RAISE("}));
  CHECK(182, write_line_num());
  CHECK(183, write(&(String){2, 1, ")"}));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write_tb_check = "write-tb-check";
#define MR_FUNC_NAME _func_name_write_tb_check
Returncode write_tb_check() {
  CHECK(186, write(&(String){7, 6, "CHECK("}));
  CHECK(187, write_line_num());
  CHECK(188, write(&(String){3, 2, ", "}));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write_spaces = "write-spaces";
#define MR_FUNC_NAME _func_name_write_spaces
Returncode write_spaces() {
  Int n; for (n = 0; n < glob->spaces; ++n) {
    CHECK(192, write_c(' '));
  }
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write_new_indent_line = "write-new-indent-line";
#define MR_FUNC_NAME _func_name_write_new_indent_line
Returncode write_new_indent_line() {
  CHECK(195, write_c('\n'));
  CHECK(196, write_spaces());
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write_type_type_params = "write-type-type-params";
#define MR_FUNC_NAME _func_name_write_type_type_params
Returncode write_type_type_params(Mtype* sub_mtype) {
  /* sizeof(name), name__dtl */
  CHECK(200, write(&(String){8, 7, "sizeof("}));
  CHECK(201, write_cstyle(sub_mtype->name));
  CHECK(202, write(&(String){4, 3, "), "}));
  if (NULL != sub_mtype->dynamic_members) {
    CHECK(204, write_cstyle(sub_mtype->name));
    CHECK(205, write(&(String){6, 5, "__dtl"}));
  }
  else {
    CHECK(207, write(&(String){5, 4, "NULL"}));
  }
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_write_type_init = "write-type-init";
#define MR_FUNC_NAME _func_name_write_type_init
Returncode write_type_init(Mtype* mtype, Mtype* sub_mtype, Bool first) {
  if (NULL != mtype->base_mtype) {
    CHECK(211, write_type_init(mtype->base_mtype, NULL, first));
    first = false;
  }
  else {
    if (mtype == glob->type_type) {
      if (!first) {
        CHECK(215, write(&(String){3, 2, ", "}));
      }
      CHECK(216, write_type_type_params(sub_mtype));
      first = false;
    }
    else {
      if (NULL != mtype->default_value) {
        if (!first) {
          CHECK(220, write(&(String){3, 2, ", "}));
        }
        CHECK(221, write(mtype->default_value));
        first = false;
      }
    }
  }
  Var_map_iter* iter = &(Var_map_iter){0};
  CHECK(224, Var_map_iter_init(iter, mtype->members));
  while (true) {
    Bool _Bool3;
    CHECK(226, Var_map_iter_m_has_data(iter, &(_Bool3)))
    if (!(_Bool3)) break;
    Mvar* mvar;
    CHECK(228, Var_map_iter_get_var(iter, &(mvar)));
    if (!(NULL != mvar->func_dec)) {
      if (mvar->access == ACCESS_VAR) {
        CHECK(231, write_type_init(mvar->mtype, mvar->sub_mtype, first));
      }
      else {
        if (!first) {
          CHECK(234, write(&(String){3, 2, ", "}));
        }
        CHECK(235, write(&(String){5, 4, "NULL"}));
      }
      first = false;
    }
    CHECK(237, Var_map_iter_m_next(iter));
  }
  return OK;
}
#undef MR_FUNC_NAME

/* syntax error */
static char* _func_name_f_syntax_error = "f-syntax-error";
#define MR_FUNC_NAME _func_name_f_syntax_error
Returncode f_syntax_error(String* text, String* item) {
  String* msg = &(String){256, 0, (char[256]){0}};
  CHECK(242, String_copy(msg, &(String){15, 14, "Code error in "}));
  CHECK(243, String_concat(msg, glob->infile_name));
  CHECK(244, String_concat(msg, &(String){2, 1, "["}));
  String* line_num_str = &(String){32, 0, (char[32]){0}};
  CHECK(246, Int_str(glob->line_num, line_num_str));
  CHECK(247, String_concat(msg, line_num_str));
  CHECK(248, String_concat(msg, &(String){3, 2, "] "}));
  CHECK(249, String_concat(msg, text));
  CHECK(250, String_concat(msg, &(String){3, 2, " \""}));
  CHECK(251, String_concat(msg, item));
  CHECK(252, String_append(msg, '\"'));
  CHECK(253, Sys_print(sys, msg));
  RAISE(254)
}
#undef MR_FUNC_NAME

static char* _func_name_f_syntax_error2 = "f-syntax-error2";
#define MR_FUNC_NAME _func_name_f_syntax_error2
Returncode f_syntax_error2(String* text1, String* item1, String* text2, String* item2) {
  String* msg = &(String){256, 0, (char[256]){0}};
  CHECK(258, String_copy(msg, text1));
  CHECK(259, String_concat(msg, &(String){3, 2, " \""}));
  CHECK(260, String_concat(msg, item1));
  CHECK(261, String_concat(msg, &(String){3, 2, "\" "}));
  CHECK(262, String_concat(msg, text2));
  CHECK(263, f_syntax_error(msg, item2));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_f_syntax_error_c = "f-syntax-error-c";
#define MR_FUNC_NAME _func_name_f_syntax_error_c
Returncode f_syntax_error_c(String* text, Char ch) {
  String* char_str = &(String){2, 0, (char[2]){0}};
  CHECK(267, String_append(char_str, ch));
  CHECK(268, f_syntax_error(text, char_str));
  return OK;
}
#undef MR_FUNC_NAME

/* other helpers */
static char* _func_name_f_get_access = "f-get-access";
#define MR_FUNC_NAME _func_name_f_get_access
Returncode f_get_access(String* access_text, Int* access) {
  Bool _Bool4;
  CHECK(272, String_equal(access_text, &(String){5, 4, "copy"}, &(_Bool4)))
  if (_Bool4) {
    (*access) = ACCESS_COPY;
  }
  else {
    Bool _Bool5;
    CHECK(274, String_equal(access_text, &(String){5, 4, "user"}, &(_Bool5)))
    if (_Bool5) {
      (*access) = ACCESS_USER;
    }
    else {
      Bool _Bool6;
      CHECK(276, String_equal(access_text, &(String){6, 5, "owner"}, &(_Bool6)))
      if (_Bool6) {
        (*access) = ACCESS_OWNER;
      }
      else {
        Bool _Bool7;
        CHECK(278, String_equal(access_text, &(String){4, 3, "var"}, &(_Bool7)))
        if (_Bool7) {
          (*access) = ACCESS_VAR;
        }
        else {
          CHECK(281, f_syntax_error(&(String){15, 14, "unknown access"}, access_text));
        }
      }
    }
  }
  return OK;
}
#undef MR_FUNC_NAME


static char* _func_name_get_node_type = "get-node-type";
#define MR_FUNC_NAME _func_name_get_node_type
Returncode get_node_type(String* key, Type* node_type, Bool* found) {
  Int n; for (n = 0; n < glob->key_word_map->length; ++n) {
    if ((n) < 0 || (n) >= glob->key_word_map->length) RAISE(286)
    Node_map_item* item = ((Node_map_item*)(glob->key_word_map->values)) + n;
    Bool _Bool8;
    CHECK(287, String_equal(item->key, key, &(_Bool8)))
    if (_Bool8) {
      (*node_type) = item->node_type;
      (*found) = true;
      return OK;
    }
  }
  (*found) = false;
  return OK;
}
#undef MR_FUNC_NAME


static char* _func_name_f_find_type = "f-find-type";
#define MR_FUNC_NAME _func_name_f_find_type
Returncode f_find_type(String* typename, Mtype** mtype) {
  CHECK(295, Type_map_find(glob->type_map, typename, &((*mtype))))
  if (NULL != (*mtype)) {
    return OK;
  }
  if (NULL != glob->mclass && NULL != glob->mclass->generic_mtype) {
    Bool _Bool9;
    CHECK(298, String_equal(typename, glob->mclass->generic_mtype->base_typename, &(_Bool9)))
    if (_Bool9) {
      (*mtype) = glob->mclass->generic_mtype;
      return OK;
    }
  }
  CHECK(301, f_syntax_error(&(String){13, 12, "unknown type"}, typename));
  return OK;
}
#undef MR_FUNC_NAME


/* basic syntax tree node */

typedef struct St St; struct St {
  Func* _dtl;
  St* next_brother;
  St* first_son;
  St* last_son;
  St* father;
  Int line_num;
  Var_map* var_map;
  Var_map* sons_var_map;
  Bool is_else;
  /* analyze sons */
  /* analyze sons */
  /* write sons */
};
static char* _func_name_St_init = "St.init";
#define MR_FUNC_NAME _func_name_St_init
Returncode St_init(St* self, St* father) {
  self->next_brother = NULL;
  self->first_son = NULL;
  self->last_son = NULL;
  self->father = father;
  self->line_num = glob->line_num;
  self->var_map = NULL;
  self->sons_var_map = NULL;
  self->is_else = false;
  if (NULL != father) {
    if (NULL != father->last_son) {
      father->last_son->next_brother = self;
    }
    father->last_son = self;
    if (!(NULL != father->first_son)) {
      father->first_son = self;
    }
    if (NULL != father->sons_var_map) {
      CHECK(332, f_copy_new_var_map(father->sons_var_map, &(self->var_map)));
    }
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_parse = "St.parse";
#define MR_FUNC_NAME _func_name_St_parse
Returncode St_parse(St* self) {
  /* do nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_analyze_first = "St.analyze-first";
#define MR_FUNC_NAME _func_name_St_analyze_first
Returncode St_analyze_first(St* self) {
  St* son = self->first_son;
  while (true) {
    if (!(NULL != son)) break;
    glob->line_num = son->line_num;
    glob->node = son;
    CHECK(344, (*((Func**)(son)))[1](son));
    son = son->next_brother;
  }
  glob->node = self;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_analyze = "St.analyze";
#define MR_FUNC_NAME _func_name_St_analyze
Returncode St_analyze(St* self) {
  St* son = self->first_son;
  while (true) {
    if (!(NULL != son)) break;
    glob->line_num = son->line_num;
    glob->node = son;
    CHECK(355, (*((Func**)(son)))[2](son));
    son = son->next_brother;
  }
  glob->node = self;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_write = "St.write";
#define MR_FUNC_NAME _func_name_St_write
Returncode St_write(St* self) {
  /* do nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_add_var = "St.add-var";
#define MR_FUNC_NAME _func_name_St_add_var
Returncode St_add_var(St* self, Mvar* mvar) {
  if (NULL != glob->mclass) {
    CHECK(365, add_var(glob->mclass->members, mvar));
  }
  else {
    if (NULL != self->father && NULL != self->father->sons_var_map) {
      CHECK(367, add_var(self->father->sons_var_map, mvar));
    }
    else {
      CHECK(369, add_var(glob->var_map, mvar));
    }
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_m_find_var = "St.m-find-var";
#define MR_FUNC_NAME _func_name_St_m_find_var
Returncode St_m_find_var(St* self, String* name, Mvar** mvar) {
  if (NULL != self->var_map) {
    CHECK(373, Var_map_find(self->var_map, name, &((*mvar))));
    if (NULL != (*mvar)) {
      return OK;
    }
  }
  if (NULL != self->father) {
    CHECK(377, St_m_find_var(self->father, name, &((*mvar))));
  }
  else {
    CHECK(379, Var_map_find(glob->var_map, name, &((*mvar))));
  }
  return OK;
}
#undef MR_FUNC_NAME
Func St__dtl[] = {St_parse, St_analyze_first, St_analyze, St_write};

static char* _func_name_f_find_var = "f-find-var";
#define MR_FUNC_NAME _func_name_f_find_var
Returncode f_find_var(String* name, Mvar** mvar) {
  CHECK(382, St_m_find_var(glob->node, name, &((*mvar))));
  return OK;
}
#undef MR_FUNC_NAME

#undef MR_FILE_NAME
