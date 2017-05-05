static char* _mr_file8_name = "dec.2.mr";
#define MR_FILE_NAME _mr_file8_name
/* MR3 compiler - variable declerations */

typedef struct St_dec St_dec; struct St_dec {
  St _base;
  Mvar* mvar;
  Mexp* value;
};
Returncode St_dec_parse_array(St_dec* self);
Returncode St_dec_parse_string(St_dec* self);
static char* _func_name_St_dec_parse = "St-dec.parse";
#define MR_FUNC_NAME _func_name_St_dec_parse
Returncode St_dec_parse(St_dec* self) {
  CHECK(11, init_new_var(NULL, &(self->mvar)));
  self->value = NULL;
  Char _Char0;
  CHECK(13, read_new(&(String){3, 2, " {"}, &(self->mvar->typename), &(_Char0)))
  if (_Char0 == '{') {
    Bool _Bool1;
    CHECK(14, String_equal(self->mvar->typename, &(String){6, 5, "Array"}, &(_Bool1)))
    if (_Bool1) {
      CHECK(15, (*((Func**)(self)))[4](self));
      Char _Char2;
      CHECK(16, read_new(&(String){3, 2, "{}"}, &(self->mvar->sub_typename), &(_Char2)))
      if (_Char2 == '{') {
        CHECK(17, (*((Func**)(self)))[5](self));
        Char _Char3;
        CHECK(18, read_c(&(_Char3)));
      }
    }
    else {
      Bool _Bool4;
      CHECK(19, String_equal(self->mvar->typename, &(String){7, 6, "String"}, &(_Bool4)))
      if (_Bool4) {
        CHECK(20, (*((Func**)(self)))[5](self));
      }
      else {
        Char _Char5;
        CHECK(22, read_new(&(String){2, 1, "}"}, &(self->mvar->sub_typename), &(_Char5)));
      }
    }
    Char _Char6;
    CHECK(23, read_c(&(_Char6)));
  }
  Char _Char7;
  CHECK(24, read_new(&(String){2, 1, "("}, &(self->mvar->name), &(_Char7)))
  if (_Char7 == '(') {
    Char _Char8;
    CHECK(25, parse_new_exp(&(String){2, 1, ")"}, &(self->value), &(_Char8)));
    Char _Char9;
    CHECK(26, read_c(&(_Char9)));
  }
  CHECK(27, St_add_var(&(self->_base), self->mvar));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_analyze_first = "St-dec.analyze-first";
#define MR_FUNC_NAME _func_name_St_dec_analyze_first
Returncode St_dec_analyze_first(St_dec* self) {
  CHECK(30, Mvar_analyze(self->mvar));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_analyze = "St-dec.analyze";
#define MR_FUNC_NAME _func_name_St_dec_analyze
Returncode St_dec_analyze(St_dec* self) {
  if (NULL != self->value) {
    CHECK(34, Mexp_analyze_types(self->value, self->mvar->mtype, self->mvar->sub_mtype));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_write = "St-dec.write";
#define MR_FUNC_NAME _func_name_St_dec_write
Returncode St_dec_write(St_dec* self) {
  if (NULL != glob->mclass) {
    if (glob->methods) {
      return OK;
    }
    CHECK(40, write_spaces());
  }
  if (NULL != self->value) {
    CHECK(42, Mexp_write_intro(self->value));
  }
  CHECK(43, write_cstyle(self->mvar->typename));
  if (!self->mvar->mtype->is_primitive) {
    CHECK(45, write(&(String){2, 1, "*"}));
  }
  CHECK(46, write(&(String){2, 1, " "}));
  CHECK(47, write_cstyle(self->mvar->name));
  Bool _Bool10;
  CHECK(48, (*((Func**)(self)))[6](self, &(_Bool10)))
  if (_Bool10) {
    CHECK(49, write(&(String){4, 3, " = "}));
    if (self->mvar->mtype == glob->type_string) {
      CHECK(51, (*((Func**)(self)))[9](self));
    }
    else {
      if (self->mvar->mtype == glob->type_array) {
        if (!(NULL != self->mvar->sub_typename)) {
          CHECK(54, f_syntax_error(&(String){22, 21, "Array type missing in"}, self->mvar->name));
        }
        CHECK(55, (*((Func**)(self)))[10](self));
      }
      else {
        if (self->mvar->mtype->is_primitive) {
          CHECK(57, (*((Func**)(self)))[7](self));
        }
        else {
          CHECK(59, (*((Func**)(self)))[8](self));
          if (NULL != self->mvar->mtype->dynamic_members) {
            /* *((Func**)(name)) = Class__dtl; */
            CHECK(62, write_new_indent_line());
            CHECK(63, write(&(String){12, 11, "*((Func**)("}));
            CHECK(64, write_cstyle(self->mvar->name));
            CHECK(65, write(&(String){6, 5, ")) = "}));
            CHECK(66, write_cstyle(self->mvar->mtype->name));
            CHECK(67, write(&(String){7, 6, "__dtl;"}));
          }
        }
      }
    }
  }
  else {
    if (NULL != self->value) {
      CHECK(70, write(&(String){4, 3, " = "}));
      CHECK(71, Mexp_write_final(self->value));
    }
    CHECK(72, write(&(String){2, 1, ";"}));
  }
  if (NULL != glob->mclass) {
    CHECK(74, write(&(String){2, 1, "\n"}));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_parse_array = "St-dec.parse-array";
#define MR_FUNC_NAME _func_name_St_dec_parse_array
Returncode St_dec_parse_array(St_dec* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_parse_string = "St-dec.parse-string";
#define MR_FUNC_NAME _func_name_St_dec_parse_string
Returncode St_dec_parse_string(St_dec* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_m_is_allocation = "St-dec.m-is-allocation";
#define MR_FUNC_NAME _func_name_St_dec_m_is_allocation
Returncode St_dec_m_is_allocation(St_dec* self, Bool* is_aloc) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_write_primitive = "St-dec.write-primitive";
#define MR_FUNC_NAME _func_name_St_dec_write_primitive
Returncode St_dec_write_primitive(St_dec* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_write_class = "St-dec.write-class";
#define MR_FUNC_NAME _func_name_St_dec_write_class
Returncode St_dec_write_class(St_dec* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_write_string = "St-dec.write-string";
#define MR_FUNC_NAME _func_name_St_dec_write_string
Returncode St_dec_write_string(St_dec* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_dec_write_array = "St-dec.write-array";
#define MR_FUNC_NAME _func_name_St_dec_write_array
Returncode St_dec_write_array(St_dec* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
Func St_dec__dtl[] = {St_dec_parse, St_dec_analyze_first, St_dec_analyze, St_dec_write, St_dec_parse_array, St_dec_parse_string, St_dec_m_is_allocation, St_dec_write_primitive, St_dec_write_class, St_dec_write_string, St_dec_write_array};


typedef struct St_var St_var; struct St_var {
  St_dec _base;
  String* arr_length;
  String* str_length;
};
static char* _func_name_St_var_parse = "St-var.parse";
#define MR_FUNC_NAME _func_name_St_var_parse
Returncode St_var_parse(St_var* self) {
  self->arr_length = NULL;
  self->str_length = NULL;
  CHECK(105, St_dec_parse(&(self->_base)));
  
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_analyze_first = "St-var.analyze-first";
#define MR_FUNC_NAME _func_name_St_var_analyze_first
Returncode St_var_analyze_first(St_var* self) {
  CHECK(108, St_dec_analyze_first(&(self->_base)));
  
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_analyze = "St-var.analyze";
#define MR_FUNC_NAME _func_name_St_var_analyze
Returncode St_var_analyze(St_var* self) {
  CHECK(111, St_dec_analyze(&(self->_base)));
  /* f-syntax-error(user "cannot initialize variable of type", user self.mvar.typename) */
  
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_write = "St-var.write";
#define MR_FUNC_NAME _func_name_St_var_write
Returncode St_var_write(St_var* self) {
  CHECK(115, St_dec_write(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_parse_array = "St-var.parse-array";
#define MR_FUNC_NAME _func_name_St_var_parse_array
Returncode St_var_parse_array(St_var* self) {
  Char _Char11;
  CHECK(118, read_new(&(String){2, 1, ":"}, &(self->arr_length), &(_Char11)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_parse_string = "St-var.parse-string";
#define MR_FUNC_NAME _func_name_St_var_parse_string
Returncode St_var_parse_string(St_var* self) {
  Char _Char12;
  CHECK(121, read_new(&(String){2, 1, "}"}, &(self->str_length), &(_Char12)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_m_is_allocation = "St-var.m-is-allocation";
#define MR_FUNC_NAME _func_name_St_var_m_is_allocation
Returncode St_var_m_is_allocation(St_var* self, Bool* is_aloc) {
  (*is_aloc) = !self->_base.mvar->mtype->is_primitive;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_write_primitive = "St-var.write-primitive";
#define MR_FUNC_NAME _func_name_St_var_write_primitive
Returncode St_var_write_primitive(St_var* self) {
  RAISE(127)
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_write_class = "St-var.write-class";
#define MR_FUNC_NAME _func_name_St_var_write_class
Returncode St_var_write_class(St_var* self) {
  /* Class* name = &(Class){0}; */
  CHECK(131, write(&(String){3, 2, "&("}));
  CHECK(132, write_cstyle(self->_base.mvar->typename));
  CHECK(133, write(&(String){6, 5, "){0};"}));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_write_string = "St-var.write-string";
#define MR_FUNC_NAME _func_name_St_var_write_string
Returncode St_var_write_string(St_var* self) {
  /* String* name = &(String){length, 0, (char[length]){0}}; */
  /* CHECK(line-num, String_copy(name, init)); */
  if (!(NULL != self->str_length)) {
    CHECK(139, f_syntax_error(&(String){25, 24, "String length missing in"}, self->_base.mvar->name));
  }
  CHECK(140, write(&(String){11, 10, "&(String){"}));
  CHECK(141, write(self->str_length));
  CHECK(142, write(&(String){12, 11, ", 0, (char["}));
  CHECK(143, write(self->str_length));
  CHECK(144, write(&(String){8, 7, "]){0}};"}));
  if (NULL != self->_base.value) {
    CHECK(146, write_new_indent_line());
    CHECK(147, write_tb_check());
    CHECK(148, write(&(String){13, 12, "String_copy("}));
    CHECK(149, write_cstyle(self->_base.mvar->name));
    CHECK(150, write(&(String){3, 2, ", "}));
    CHECK(151, Mexp_write_final(self->_base.value));
    CHECK(152, write(&(String){3, 2, "))"}));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_var_write_array = "St-var.write-array";
#define MR_FUNC_NAME _func_name_St_var_write_array
Returncode St_var_write_array(St_var* self) {
  /* Array* name = &(Array){length, (Class[length]){0}}; */
  /* Array* name = &(Array){length, (String[length]){0}}; */
  /* _set_var_string_array(length, string-length, name, (char[string-length * length]){0}); */
  if (!(NULL != self->arr_length)) {
    CHECK(159, f_syntax_error(&(String){24, 23, "Array length missing in"}, self->_base.mvar->name));
  }
  CHECK(160, write(&(String){10, 9, "&(Array){"}));
  CHECK(161, write(self->arr_length));
  CHECK(162, write(&(String){4, 3, ", ("}));
  CHECK(163, write_cstyle(self->_base.mvar->sub_typename));
  CHECK(164, write(&(String){2, 1, "["}));
  CHECK(165, write(self->arr_length));
  CHECK(166, write(&(String){8, 7, "]){0}};"}));
  if (NULL != self->str_length) {
    CHECK(168, write_new_indent_line());
    CHECK(169, write(&(String){23, 22, "_set_var_string_array("}));
    CHECK(170, write(self->arr_length));
    CHECK(171, write(&(String){3, 2, ", "}));
    CHECK(172, write(self->str_length));
    CHECK(173, write(&(String){3, 2, ", "}));
    CHECK(174, write_cstyle(self->_base.mvar->name));
    CHECK(175, write(&(String){9, 8, ", (char["}));
    CHECK(176, write(self->str_length));
    CHECK(177, write(&(String){4, 3, " * "}));
    CHECK(178, write(self->arr_length));
    CHECK(179, write(&(String){8, 7, "]){0});"}));
  }
  return OK;
}
#undef MR_FUNC_NAME
Func St_var__dtl[] = {St_var_parse, St_var_analyze_first, St_var_analyze, St_var_write, St_var_parse_array, St_var_parse_string, St_var_m_is_allocation, St_var_write_primitive, St_var_write_class, St_var_write_string, St_var_write_array};


typedef struct St_ref St_ref; struct St_ref {
  St_dec _base;
};
static char* _func_name_St_ref_parse = "St-ref.parse";
#define MR_FUNC_NAME _func_name_St_ref_parse
Returncode St_ref_parse(St_ref* self) {
  CHECK(184, St_dec_parse(&(self->_base)));
  self->_base.mvar->access = ACCESS_USER;
  
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_analyze_first = "St-ref.analyze-first";
#define MR_FUNC_NAME _func_name_St_ref_analyze_first
Returncode St_ref_analyze_first(St_ref* self) {
  CHECK(188, St_dec_analyze_first(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_analyze = "St-ref.analyze";
#define MR_FUNC_NAME _func_name_St_ref_analyze
Returncode St_ref_analyze(St_ref* self) {
  CHECK(191, St_dec_analyze(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_write = "St-ref.write";
#define MR_FUNC_NAME _func_name_St_ref_write
Returncode St_ref_write(St_ref* self) {
  CHECK(194, St_dec_write(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_parse_array = "St-ref.parse-array";
#define MR_FUNC_NAME _func_name_St_ref_parse_array
Returncode St_ref_parse_array(St_ref* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_parse_string = "St-ref.parse-string";
#define MR_FUNC_NAME _func_name_St_ref_parse_string
Returncode St_ref_parse_string(St_ref* self) {
  CHECK(200, f_syntax_error(&(String){31, 30, "unexpected parameter to String"}, &(String){1, 0, ""}));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_m_is_allocation = "St-ref.m-is-allocation";
#define MR_FUNC_NAME _func_name_St_ref_m_is_allocation
Returncode St_ref_m_is_allocation(St_ref* self, Bool* is_aloc) {
  (*is_aloc) = false;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_write_primitive = "St-ref.write-primitive";
#define MR_FUNC_NAME _func_name_St_ref_write_primitive
Returncode St_ref_write_primitive(St_ref* self) {
  RAISE(206)
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_write_class = "St-ref.write-class";
#define MR_FUNC_NAME _func_name_St_ref_write_class
Returncode St_ref_write_class(St_ref* self) {
  RAISE(209)
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_write_string = "St-ref.write-string";
#define MR_FUNC_NAME _func_name_St_ref_write_string
Returncode St_ref_write_string(St_ref* self) {
  RAISE(212)
}
#undef MR_FUNC_NAME
static char* _func_name_St_ref_write_array = "St-ref.write-array";
#define MR_FUNC_NAME _func_name_St_ref_write_array
Returncode St_ref_write_array(St_ref* self) {
  RAISE(215)
}
#undef MR_FUNC_NAME
Func St_ref__dtl[] = {St_ref_parse, St_ref_analyze_first, St_ref_analyze, St_ref_write, St_ref_parse_array, St_ref_parse_string, St_ref_m_is_allocation, St_ref_write_primitive, St_ref_write_class, St_ref_write_string, St_ref_write_array};


typedef struct St_new St_new; struct St_new {
  St_var _base;
  Mexp* arr_length;
  Mexp* str_length;
};
static char* _func_name_St_new_parse = "St-new.parse";
#define MR_FUNC_NAME _func_name_St_new_parse
Returncode St_new_parse(St_new* self) {
  CHECK(223, St_var_parse(&(self->_base)));
  self->_base._base.mvar->access = ACCESS_OWNER;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_analyze_first = "St-new.analyze-first";
#define MR_FUNC_NAME _func_name_St_new_analyze_first
Returncode St_new_analyze_first(St_new* self) {
  CHECK(227, St_var_analyze_first(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_analyze = "St-new.analyze";
#define MR_FUNC_NAME _func_name_St_new_analyze
Returncode St_new_analyze(St_new* self) {
  if (NULL != self->_base._base.value) {
    CHECK(231, f_syntax_error(&(String){21, 20, "cannot initialize in"}, &(String){4, 3, "new"}));
  }
  if (NULL != self->str_length) {
    CHECK(233, Mexp_analyze_type(self->str_length, glob->type_int));
  }
  if (NULL != self->arr_length) {
    CHECK(235, Mexp_analyze_type(self->arr_length, glob->type_int));
  }
  CHECK(236, St_var_analyze(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_write = "St-new.write";
#define MR_FUNC_NAME _func_name_St_new_write
Returncode St_new_write(St_new* self) {
  CHECK(239, St_var_write(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_parse_array = "St-new.parse-array";
#define MR_FUNC_NAME _func_name_St_new_parse_array
Returncode St_new_parse_array(St_new* self) {
  Char _Char13;
  CHECK(242, parse_new_exp(&(String){2, 1, ":"}, &(self->arr_length), &(_Char13)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_parse_string = "St-new.parse-string";
#define MR_FUNC_NAME _func_name_St_new_parse_string
Returncode St_new_parse_string(St_new* self) {
  Char _Char14;
  CHECK(245, parse_new_exp(&(String){2, 1, "}"}, &(self->str_length), &(_Char14)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_m_is_allocation = "St-new.m-is-allocation";
#define MR_FUNC_NAME _func_name_St_new_m_is_allocation
Returncode St_new_m_is_allocation(St_new* self, Bool* is_aloc) {
  (*is_aloc) = true;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_write_check = "St-new.write-check";
#define MR_FUNC_NAME _func_name_St_new_write_check
Returncode St_new_write_check(St_new* self) {
  /* if (name == NULL) RAISE(line-num) */
  CHECK(252, write_new_indent_line());
  CHECK(253, write(&(String){5, 4, "if ("}));
  CHECK(254, write_cstyle(self->_base._base.mvar->name));
  CHECK(255, write(&(String){11, 10, " == NULL) "}));
  CHECK(256, write_tb_raise());
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_write_primitive = "St-new.write-primitive";
#define MR_FUNC_NAME _func_name_St_new_write_primitive
Returncode St_new_write_primitive(St_new* self) {
  CHECK(259, f_syntax_error(&(String){33, 32, "new not supported for primitive "}, self->_base._base.mvar->name));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_write_class = "St-new.write-class";
#define MR_FUNC_NAME _func_name_St_new_write_class
Returncode St_new_write_class(St_new* self) {
  /* Class* name = malloc(sizeof(Class)); */
  CHECK(263, write(&(String){15, 14, "malloc(sizeof("}));
  CHECK(264, write_cstyle(self->_base._base.mvar->typename));
  CHECK(265, write(&(String){4, 3, "));"}));
  CHECK(266, St_new_write_check(self));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_write_string = "St-new.write-string";
#define MR_FUNC_NAME _func_name_St_new_write_string
Returncode St_new_write_string(St_new* self) {
  /* String* name = new_string(length); */
  if (!(NULL != self->str_length)) {
    CHECK(271, f_syntax_error(&(String){25, 24, "String length missing in"}, self->_base._base.mvar->name));
  }
  CHECK(272, Mexp_write_intro(self->str_length));
  CHECK(273, write(&(String){13, 12, "_new_string("}));
  CHECK(274, Mexp_write_final(self->str_length));
  CHECK(275, write(&(String){3, 2, ");"}));
  CHECK(276, St_new_write_check(self));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_new_write_array = "St-new.write-array";
#define MR_FUNC_NAME _func_name_St_new_write_array
Returncode St_new_write_array(St_new* self) {
  /* Array* name = new_array(length, sizeof(Class)); */
  /* Array* name = new_array(length, sizeof(String) + (string-length)); */
  /* _set_new_string_array(length, string-length, name); */
  if (!(NULL != self->arr_length)) {
    CHECK(283, f_syntax_error(&(String){24, 23, "Array length missing in"}, self->_base._base.mvar->name));
  }
  CHECK(284, Mexp_write_intro(self->arr_length));
  if (NULL != self->str_length) {
    CHECK(286, Mexp_write_intro(self->str_length));
  }
  CHECK(287, write(&(String){12, 11, "_new_array("}));
  CHECK(288, Mexp_write_final(self->arr_length));
  CHECK(289, write(&(String){10, 9, ", sizeof("}));
  CHECK(290, write_cstyle(self->_base._base.mvar->sub_typename));
  if (NULL != self->str_length) {
    CHECK(292, write(&(String){6, 5, ") + ("}));
    CHECK(293, Mexp_write_final(self->str_length));
  }
  CHECK(294, write(&(String){4, 3, "));"}));
  CHECK(295, St_new_write_check(self));
  if (NULL != self->str_length) {
    CHECK(297, write_new_indent_line());
    CHECK(298, write(&(String){23, 22, "_set_new_string_array("}));
    CHECK(299, Mexp_write_final(self->arr_length));
    CHECK(300, write(&(String){3, 2, ", "}));
    CHECK(301, Mexp_write_final(self->str_length));
    CHECK(302, write(&(String){3, 2, ", "}));
    CHECK(303, write_cstyle(self->_base._base.mvar->name));
    CHECK(304, write(&(String){3, 2, ");"}));
  }
  return OK;
}
#undef MR_FUNC_NAME
Func St_new__dtl[] = {St_new_parse, St_new_analyze_first, St_new_analyze, St_new_write, St_new_parse_array, St_new_parse_string, St_new_m_is_allocation, St_new_write_primitive, St_new_write_class, St_new_write_string, St_new_write_array};


typedef struct St_delete St_delete; struct St_delete {
  St _base;
  String* name;
  Mvar* mvar;
};
static char* _func_name_St_delete_parse = "St-delete.parse";
#define MR_FUNC_NAME _func_name_St_delete_parse
Returncode St_delete_parse(St_delete* self) {
  Char _Char15;
  CHECK(312, read_new(&(String){1, 0, ""}, &(self->name), &(_Char15)));
  self->mvar = NULL;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_delete_analyze_first = "St-delete.analyze-first";
#define MR_FUNC_NAME _func_name_St_delete_analyze_first
Returncode St_delete_analyze_first(St_delete* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_delete_analyze = "St-delete.analyze";
#define MR_FUNC_NAME _func_name_St_delete_analyze
Returncode St_delete_analyze(St_delete* self) {
  CHECK(319, m_find_var(self->name, &(self->mvar)))
  if (!(NULL != self->mvar)) {
    CHECK(320, f_syntax_error(&(String){16, 15, "unknow variable"}, self->name));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_delete_write = "St-delete.write";
#define MR_FUNC_NAME _func_name_St_delete_write
Returncode St_delete_write(St_delete* self) {
  CHECK(323, write(&(String){6, 5, "free("}));
  CHECK(324, write_cstyle(self->name));
  CHECK(325, write(&(String){3, 2, ");"}));
  return OK;
}
#undef MR_FUNC_NAME
Func St_delete__dtl[] = {St_delete_parse, St_delete_analyze_first, St_delete_analyze, St_delete_write};

#undef MR_FILE_NAME
