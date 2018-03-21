#ifndef LUMI_MAINFILE
#define LUMI_MAINFILE "statement/type.c"
#define DEPTH 5
#include "lumi.3.h"
#else

#if LUMI_STAGE == LUMI_TYPEDEFS
static char* _lumi_file29_name = "statement/type.3.lm";
#endif
#define LUMI_FILE_NAME _lumi_file29_name

/* TL4 compiler - Syntax tree type */

/* Type node in the syntax tree  */
#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct TypeData TypeData;
#elif LUMI_STAGE == LUMI_TYPES(3)
struct TypeData {
  SyntaxTreeNamespace _base;
  String* name;
  ModuleMembers* my_module;
  TypeInstance* base_type;
  List* parameters;
  NameMap* dynamic_base_methods;
  SyntaxTreeConstructor* constructor;
  Bool is_primitive;
  Bool is_dynamic;
  Bool is_ordered;
  Bool is_delete_mocked;
  Bool ordering;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_parse_new(TypeData* self, Bool is_dynamic, Char* end, TypeData** new_node);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_parse_new = "TypeData.parse-new";
#define LUMI_FUNC_NAME _func_name_TypeData_parse_new
Returncode TypeData_parse_new(TypeData* self, Bool is_dynamic, Char* end, TypeData** new_node) {
  (*new_node) = malloc(sizeof(TypeData));
  if ((*new_node) == NULL) RAISE(19)
  *(*new_node) = (TypeData){TypeData__dtl, NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, false, false, false, false, false};
  (*new_node)->_base._base._base._dtl = TypeData__dtl;
  CHECK(20, TypeData_parse((*new_node), is_dynamic, &((*end))) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_parse(TypeData* self, Bool is_dynamic, Char* end);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_parse = "TypeData.parse";
#define LUMI_FUNC_NAME _func_name_TypeData_parse
Returncode TypeData_parse(TypeData* self, Bool is_dynamic, Char* end) {
  self->is_dynamic = is_dynamic;
  CHECK(24, SyntaxTreeNode_set_location(&(self->_base._base._base)) )
  self->my_module = glob->current_module;
  CHECK(26, read_new(&(String){3, 2, "({"}, &(self->name), &((*end))) )
  CHECK(27, TypeData_add_type(self, self->my_module) )
  if ((*end) == '{') {
    self->parameters = malloc(sizeof(List));
    if (self->parameters == NULL) RAISE(29)
    *self->parameters = (List){NULL, NULL};
    while (true) {
      String* name = NULL;
      CHECK(32, read_new(&(String){3, 2, ":}"}, &(name), &((*end))) )
      Bool _Bool171;
      CHECK(33, f_is_legal_name(name, NAME_TYPE, &(_Bool171)) )
      if (!_Bool171) {
        CHECK(34, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){28, 27, "illegal type parameter name"}, name) )
      }
      CHECK(35, List_add(self->parameters, name) )
      if (!((*end) == ':')) break;
    }
    if ((*end) != '}') {
      CHECK(38, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){40, 39, "expected \"}\" after type parameters, got"}, (*end)) )
    }
    CHECK(40, read_c(&((*end))) )
  }
  if ((*end) == '(') {
    self->base_type = malloc(sizeof(TypeInstance));
    if (self->base_type == NULL) RAISE(42)
    *self->base_type = (TypeInstance){NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    CHECK(43, TypeInstance_parse(self->base_type, &(String){2, 1, ")"}, &(self->_base._base._base), NULL, &((*end))) )
    if ((*end) != ')') {
      CHECK(45, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){34, 33, "expected \")\" after base type, got"}, (*end)) )
    }
    CHECK(47, read_c(&((*end))) )
  }
  self->_base._base.indentation_spaces = 2;
  CHECK(49, SyntaxTreeBranch_parse_block_children(&(self->_base._base), self, NULL, &((*end))) )
  self->_base._base.indentation_spaces = 0;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_add_type(TypeData* self, ModuleMembers* my_module);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_add_type = "TypeData.add-type";
#define LUMI_FUNC_NAME _func_name_TypeData_add_type
Returncode TypeData_add_type(TypeData* self, ModuleMembers* my_module) {
  Bool _Bool172;
  CHECK(53, f_is_legal_name(self->name, NAME_TYPE, &(_Bool172)) )
  if (!_Bool172) {
    CHECK(54, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){18, 17, "illegal type name"}, self->name) )
  }
  TypeData* _TypeData173;
  CHECK(55, Global_find_type(glob, self->name, &(_TypeData173)) )
  if (NULL != _TypeData173) {
    CHECK(56, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){21, 20, "redefinition of type"}, self->name) )
  }
  EnumData* _EnumData174;
  CHECK(57, NameMap_find(glob->current_module->enum_map, self->name, (void**)&(_EnumData174)) )
  if (NULL != _EnumData174) {
    CHECK(58, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){25, 24, "type name overrides Enum"}, self->name) )
  }
  CHECK(59, SyntaxTreeNamespace_init(&(self->_base)) )
  CHECK(60, NameMap_add(my_module->type_map, self->name, self) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_parse_child(TypeData* self, String* keyword, Char* end);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_parse_child = "TypeData.parse-child";
#define LUMI_FUNC_NAME _func_name_TypeData_parse_child
Returncode TypeData_parse_child(TypeData* self, String* keyword, Char* end) {
  Bool _Bool175;
  CHECK(63, SyntaxTreeNamespace_parse_if_function(&(self->_base), keyword, self, &((*end)), &(_Bool175)) )
  if (_Bool175) {
    return OK;
  }
  
  Bool _Bool176;
  CHECK(66, String_equal(keyword, &(String){4, 3, "new"}, &(_Bool176)) )
  if (_Bool176) {
    if ((*end) != '(') {
      CHECK(68, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){30, 29, "expected \"(\" after \"new\", got"}, (*end)) )
    }
    if (NULL != self->constructor) {
      CHECK(71, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){37, 36, "constructor already defined for type"}, self->name) )
    }
    SyntaxTreeConstructor* constructor = NULL;
    CHECK(74, SyntaxTreeConstructor_parse_new(NULL, self, &((*end)), &(constructor)) )
    self->constructor = constructor;
    CHECK(76, List_add(self->_base.functions, &(constructor->_base)) )
    
  }
  else {
    CHECK(79, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){16, 15, "unknown keyword"}, keyword) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_m_is_same(TypeData* self, TypeData* other, Bool* is_same);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_m_is_same = "TypeData.m-is-same";
#define LUMI_FUNC_NAME _func_name_TypeData_m_is_same
Returncode TypeData_m_is_same(TypeData* self, TypeData* other, Bool* is_same) {
  (*is_same) = self == other || ((self == glob->type_int || self == glob->type_char) && (other == glob->type_int || other == glob->type_char));
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_m_new_type_instance(TypeData* self, TypeInstance** type_instance);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_m_new_type_instance = "TypeData.m-new-type-instance";
#define LUMI_FUNC_NAME _func_name_TypeData_m_new_type_instance
Returncode TypeData_m_new_type_instance(TypeData* self, TypeInstance** type_instance) {
  (*type_instance) = malloc(sizeof(TypeInstance));
  if ((*type_instance) == NULL) RAISE(87)
  *(*type_instance) = (TypeInstance){NULL, NULL, NULL, NULL, NULL, NULL, NULL};
  (*type_instance)->type_data = self;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_m_self_type_instance(TypeData* self, TypeInstance** type_instance);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_m_self_type_instance = "TypeData.m-self-type-instance";
#define LUMI_FUNC_NAME _func_name_TypeData_m_self_type_instance
Returncode TypeData_m_self_type_instance(TypeData* self, TypeInstance** type_instance) {
  CHECK(91, TypeData_m_new_type_instance(self, &((*type_instance))) )
  if (NULL != self->parameters) {
    (*type_instance)->parameters = malloc(sizeof(List));
    if ((*type_instance)->parameters == NULL) RAISE(93)
    *(*type_instance)->parameters = (List){NULL, NULL};
    ListNode* node = self->parameters->first;
    while (true) {
      if (!(NULL != node)) break;
      TypeInstance* parameter = malloc(sizeof(TypeInstance));
      if (parameter == NULL) RAISE(97)
      *parameter = (TypeInstance){NULL, NULL, NULL, NULL, NULL, NULL, NULL};
      parameter->type_data = glob->type_generic;
      CHECK(99, string_new_copy(node->item, &(parameter->name)) )
      CHECK(100, List_add((*type_instance)->parameters, parameter) )
      node = node->next;
    }
  }
  
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_get_parent_type(TypeData* self, TypeData** parent_type);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_get_parent_type = "TypeData.get-parent-type";
#define LUMI_FUNC_NAME _func_name_TypeData_get_parent_type
Returncode TypeData_get_parent_type(TypeData* self, TypeData** parent_type) {
  (*parent_type) = self;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_find_field(TypeData* self, String* name, SyntaxTreeVariable** field, Int* bases);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_find_field = "TypeData.find-field";
#define LUMI_FUNC_NAME _func_name_TypeData_find_field
Returncode TypeData_find_field(TypeData* self, String* name, SyntaxTreeVariable** field, Int* bases) {
  TypeData* type_data = self;
  (*bases) = 0;
  while (true) {
    if (!(NULL != type_data)) break;
    ListNode* child = type_data->_base._base.variables->first;
    while (true) {
      if (!(NULL != child)) break;
      Bool _Bool177;
      CHECK(116, String_equal(((SyntaxTreeVariable*)(child->item))->name, name, &(_Bool177)) )
      if (_Bool177) {
        (*field) = ((SyntaxTreeVariable*)(child->item));
        return OK;
      }
      child = child->next;
    }
    if (!(NULL != type_data->base_type)) break;
    type_data = type_data->base_type->type_data;
    (*bases) += 1;
  }
  (*field) = NULL;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_find_meth(TypeData* self, String* name, SyntaxTreeFunction** method, Int* bases);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_find_meth = "TypeData.find-meth";
#define LUMI_FUNC_NAME _func_name_TypeData_find_meth
Returncode TypeData_find_meth(TypeData* self, String* name, SyntaxTreeFunction** method, Int* bases) {
  TypeData* type_data = self;
  (*bases) = 0;
  while (true) {
    if (!(NULL != type_data)) break;
    ListNode* child = type_data->_base.functions->first;
    while (true) {
      if (!(NULL != child)) break;
      Bool _Bool178;
      CHECK(134, String_equal(((SyntaxTreeFunction*)(child->item))->name, name, &(_Bool178)) )
      if (_Bool178) {
        (*method) = ((SyntaxTreeFunction*)(child->item));
        return OK;
      }
      child = child->next;
    }
    if (!(NULL != type_data->base_type)) break;
    type_data = type_data->base_type->type_data;
    (*bases) += 1;
  }
  (*method) = NULL;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_m_order_bases(TypeData* self, List* ordered_list);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_m_order_bases = "TypeData.m-order-bases";
#define LUMI_FUNC_NAME _func_name_TypeData_m_order_bases
Returncode TypeData_m_order_bases(TypeData* self, List* ordered_list) {
  if (self->is_ordered) {
    return OK;
  }
  if (self->ordering) {
    CHECK(147, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){30, 29, "recursive inheritance in type"}, self->name) )
  }
  self->ordering = true;
  if (NULL != self->base_type) {
    glob->current_module = self->my_module;
    CHECK(152, TypeInstance_link_types(self->base_type, &(self->_base._base._base)) )
    glob->current_module = NULL;
    CHECK(154, TypeData_m_order_bases(self->base_type->type_data, ordered_list) )
  }
  CHECK(155, List_add(ordered_list, self) )
  self->is_ordered = true;
  /* init `self.dynamic-base-methods` and test override methods */
  if (self->is_dynamic) {
    self->dynamic_base_methods = malloc(sizeof(NameMap));
    if (self->dynamic_base_methods == NULL) RAISE(159)
    *self->dynamic_base_methods = (NameMap){NULL, NULL};
  }
  ListNode* child = self->_base.functions->first;
  while (true) {
    if (!(NULL != child)) break;
    SyntaxTreeFunction* method = NULL;
    Int bases = 0;
    if (NULL != self->base_type) {
      CHECK(166, TypeData_find_meth(self->base_type->type_data, ((SyntaxTreeFunction*)(child->item))->name, &(method), &(bases)) )
    }
    if (NULL != method) {
      CHECK(169, SyntaxTreeFunction_m_compare(((SyntaxTreeFunction*)(child->item)), method) )
      if (((SyntaxTreeFunction*)(child->item))->is_dynamic) {
        ((SyntaxTreeFunction*)(child->item))->dynamic_base_method = method->dynamic_base_method;
        ((SyntaxTreeFunction*)(child->item))->dynamic_base_count = method->dynamic_base_count + bases + 1;
      }
    }
    else {
      if (((SyntaxTreeFunction*)(child->item))->is_dynamic) {
        ((SyntaxTreeFunction*)(child->item))->dynamic_base_method = ((SyntaxTreeFunction*)(child->item));
        CHECK(175, NameMap_add(self->dynamic_base_methods, ((SyntaxTreeFunction*)(child->item))->name, child->item) )
      }
    }
    child = child->next;
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_link_types(TypeData* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_link_types = "TypeData.link-types";
#define LUMI_FUNC_NAME _func_name_TypeData_link_types
Returncode TypeData_link_types(TypeData* self) {
  glob->current_module = self->my_module;
  if (NULL != self->base_type) {
    CHECK(181, TypeInstance_link_types(self->base_type, &(self->_base._base._base)) )
  }
  CHECK(182, SyntaxTreeNamespace_link_types(&(self->_base)) )
  glob->current_module = NULL;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_analyze(TypeData* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_analyze = "TypeData.analyze";
#define LUMI_FUNC_NAME _func_name_TypeData_analyze
Returncode TypeData_analyze(TypeData* self) {
  glob->current_module = self->my_module;
  if (NULL != self->base_type) {
    CHECK(188, TypeInstance_analyze_lengths(self->base_type, &(self->_base._base._base), true) )
  }
  Bool _Bool179;
  CHECK(189, List_m_is_empty(self->_base._base.variables, &(_Bool179)) )
  if (!(NULL != self->base_type) && _Bool179) {
    CHECK(190, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){20, 19, "type with no fields"}, self->name) )
  }
  if (self->is_dynamic &&  ! (NULL != self->base_type && self->base_type->type_data->is_dynamic)) {
    ListNode* node = self->_base.functions->first;
    while (true) {
      if (!(NULL != node)) {
        CHECK(196, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){30, 29, "class with no dynamic methods"}, self->name) )
      }
      if (!(!((SyntaxTreeFunction*)(node->item))->is_dynamic)) break;
      node = node->next;
    }
  }
  CHECK(200, SyntaxTreeNamespace_analyze(&(self->_base)) )
  glob->current_module = NULL;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_write_cname(TypeData* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_write_cname = "TypeData.write-cname";
#define LUMI_FUNC_NAME _func_name_TypeData_write_cname
Returncode TypeData_write_cname(TypeData* self) {
  if (NULL != self->my_module) {
    CHECK(205, ModuleMembers_write_prefix(self->my_module) )
  }
  CHECK(206, write_cname(self->name) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_write_declaration(TypeData* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_write_declaration = "TypeData.write-declaration";
#define LUMI_FUNC_NAME _func_name_TypeData_write_declaration
Returncode TypeData_write_declaration(TypeData* self) {
  /* typedef struct `name` `name`; */
  /* typedef struct `name`_Dynamic `name`_Dynamic; */
  CHECK(211, write(&(String){17, 16, "\ntypedef struct "}) )
  CHECK(212, TypeData_write_cname(self) )
  CHECK(213, write(&(String){2, 1, " "}) )
  CHECK(214, TypeData_write_cname(self) )
  CHECK(215, write(&(String){3, 2, ";\n"}) )
  if (self->is_dynamic) {
    CHECK(217, write(&(String){17, 16, "\ntypedef struct "}) )
    CHECK(218, TypeData_write_cname(self) )
    CHECK(219, write(&(String){10, 9, "_Dynamic "}) )
    CHECK(220, TypeData_write_cname(self) )
    CHECK(221, write(&(String){11, 10, "_Dynamic;\n"}) )
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_write(TypeData* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_write = "TypeData.write";
#define LUMI_FUNC_NAME _func_name_TypeData_write
Returncode TypeData_write(TypeData* self) {
  /* struct `name` { */
  /*   `variables...` */
  /* }; */
  /* struct `name`_Dynamic { */
  /*   `dynamic-function-pointers...` */
  /* }; */
  CHECK(230, write(&(String){9, 8, "\nstruct "}) )
  CHECK(231, TypeData_write_cname(self) )
  CHECK(232, write(&(String){4, 3, " {\n"}) )
  self->_base._base.indentation_spaces = 2;
  if (NULL != self->base_type) {
    CHECK(235, SyntaxTreeBranch_write_spaces(&(self->_base._base)) )
    CHECK(236, TypeData_write_cname(self->base_type->type_data) )
    CHECK(237, write(&(String){9, 8, " _base;\n"}) )
  }
  CHECK(238, SyntaxTreeNode_write_children(&(self->_base._base._base), self->_base._base.variables) )
  CHECK(239, write(&(String){4, 3, "};\n"}) )
  if (self->is_dynamic) {
    CHECK(241, write(&(String){9, 8, "\nstruct "}) )
    CHECK(242, TypeData_write_cname(self) )
    CHECK(243, write(&(String){12, 11, "_Dynamic {\n"}) )
    if (NULL != self->base_type && self->base_type->type_data->is_dynamic) {
      CHECK(245, SyntaxTreeBranch_write_spaces(&(self->_base._base)) )
      CHECK(246, TypeData_write_cname(self->base_type->type_data) )
      CHECK(247, write(&(String){17, 16, "_Dynamic _base;\n"}) )
    }
    else {
      CHECK(249, SyntaxTreeBranch_write_spaces(&(self->_base._base)) )
      CHECK(250, write(&(String){19, 18, "Dynamic_Del _del;\n"}) )
    }
    NameMapNode* child = self->dynamic_base_methods->first;
    while (true) {
      if (!(NULL != child)) break;
      CHECK(254, SyntaxTreeBranch_write_spaces(&(self->_base._base)) )
      CHECK(255, SyntaxTreeFunction_write_pointer(((SyntaxTreeFunction*)(child->value))) )
      CHECK(256, write(&(String){3, 2, ";\n"}) )
      child = child->next;
    }
    CHECK(258, write(&(String){4, 3, "};\n"}) )
  }
  self->_base._base.indentation_spaces = 0;
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_write_methods_declaration(TypeData* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_write_methods_declaration = "TypeData.write-methods-declaration";
#define LUMI_FUNC_NAME _func_name_TypeData_write_methods_declaration
Returncode TypeData_write_methods_declaration(TypeData* self) {
  CHECK(262, SyntaxTreeNamespace_write_functions_declaration(&(self->_base)) )
  /* void `cname`_Del(`cname`* self); */
  CHECK(264, write(&(String){7, 6, "\nvoid "}) )
  CHECK(265, TypeData_write_cname(self) )
  CHECK(266, write(&(String){6, 5, "_Del("}) )
  CHECK(267, TypeData_write_cname(self) )
  CHECK(268, write(&(String){10, 9, "* self);\n"}) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_write_global(TypeData* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_write_global = "TypeData.write-global";
#define LUMI_FUNC_NAME _func_name_TypeData_write_global
Returncode TypeData_write_global(TypeData* self) {
  CHECK(271, write(&(String){2, 1, "\n"}) )
  if (self->is_dynamic) {
    /* `name`_Dynamic `name`_dynamic = {`dynamic-functions...`}; */
    CHECK(274, TypeData_write_cname(self) )
    CHECK(275, write(&(String){10, 9, "_Dynamic "}) )
    CHECK(276, TypeData_write_cname(self) )
    CHECK(277, write(&(String){12, 11, "_dynamic = "}) )
    CHECK(278, TypeData_write_dynamic_init(self, self) )
  }
  else {
    /* Generic_Type_Dynamic `name`_dynamic = {(Dynamic_Del)`name`_Del}; */
    CHECK(281, write(&(String){22, 21, "Generic_Type_Dynamic "}) )
    CHECK(282, TypeData_write_cname(self) )
    CHECK(283, write(&(String){26, 25, "_dynamic = {(Dynamic_Del)"}) )
    CHECK(284, TypeData_write_cname(self) )
    CHECK(285, write(&(String){6, 5, "_Del}"}) )
  }
  CHECK(286, write(&(String){3, 2, ";\n"}) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_write_dynamic_init(TypeData* self, TypeData* type_data);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_write_dynamic_init = "TypeData.write-dynamic-init";
#define LUMI_FUNC_NAME _func_name_TypeData_write_dynamic_init
Returncode TypeData_write_dynamic_init(TypeData* self, TypeData* type_data) {
  CHECK(289, write(&(String){2, 1, "{"}) )
  if (NULL != type_data->base_type && type_data->base_type->type_data->is_dynamic) {
    CHECK(291, TypeData_write_dynamic_init(self, type_data->base_type->type_data) )
  }
  else {
    CHECK(293, write(&(String){14, 13, "(Dynamic_Del)"}) )
    CHECK(294, TypeData_write_cname(self) )
    CHECK(295, write(&(String){5, 4, "_Del"}) )
  }
  NameMapNode* child = type_data->dynamic_base_methods->first;
  while (true) {
    if (!(NULL != child)) break;
    SyntaxTreeFunction* method = NULL;
    Int _Int180;
    CHECK(300, TypeData_find_meth(self, ((SyntaxTreeFunction*)(child->value))->name, &(method), &(_Int180)) )
    CHECK(301, write(&(String){3, 2, ", "}) )
    if (method != ((SyntaxTreeFunction*)(child->value))) {
      CHECK(303, write(&(String){7, 6, "(Func)"}) )
    }
    CHECK(304, TypeData_write_cname(method->parent_type) )
    CHECK(305, write(&(String){2, 1, "_"}) )
    if (NULL != method->mocker_function) {
      CHECK(307, write_cname(method->mocker_function->_base.name) )
    }
    else {
      CHECK(309, write_cname(method->name) )
    }
    child = child->next;
  }
  CHECK(311, write(&(String){2, 1, "}"}) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_write_methods_body(TypeData* self);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_write_methods_body = "TypeData.write-methods-body";
#define LUMI_FUNC_NAME _func_name_TypeData_write_methods_body
Returncode TypeData_write_methods_body(TypeData* self) {
  CHECK(314, SyntaxTreeNode_write_children(&(self->_base._base._base), self->_base.functions) )
  /* void `cname`_Del(`cname`* self) { */
  /*   if (self == NULL) return; */
  /*   `base`_Del(self); */
  /*   ... */
  /* } */
  CHECK(320, write(&(String){7, 6, "\nvoid "}) )
  CHECK(321, TypeData_write_cname(self) )
  CHECK(322, write(&(String){6, 5, "_Del("}) )
  CHECK(323, TypeData_write_cname(self) )
  CHECK(324, write(&(String){11, 10, "* self) {\n"}) )
  CHECK(325, write(&(String){29, 28, "  if (self == NULL) return;\n"}) )
  if (NULL != self->base_type) {
    CHECK(327, write(&(String){3, 2, "  "}) )
    CHECK(328, TypeData_write_cname(self->base_type->type_data) )
    CHECK(329, write(&(String){23, 22, "_Del(&(self->_base));\n"}) )
  }
  if (self->is_delete_mocked) {
    CHECK(331, write(&(String){18, 17, "  IGNORE_ERRORS( "}) )
    CHECK(332, TypeData_write_cname(self) )
    CHECK(333, write(&(String){18, 17, "_MockDel(self) )\n"}) )
  }
  CHECK(334, SyntaxTreeBranch_write_cleanup(&(self->_base._base), self) )
  CHECK(335, write(&(String){3, 2, "}\n"}) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeData_write_me(TypeData* self, TypeWriter* type_writer);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeData_write_me = "TypeData.write-me";
#define LUMI_FUNC_NAME _func_name_TypeData_write_me
Returncode TypeData_write_me(TypeData* self, TypeWriter* type_writer) {
  CHECK(338, (type_writer)->_dtl[0](type_writer, self) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func TypeData__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func TypeData__dtl[] = {(void*)TypeData_get_parent_type, (void*)TypeData_link_types, (void*)TypeData_analyze, (void*)SyntaxTreeNode_m_order_constants, (void*)TypeData_write, (void*)SyntaxTreeBranch_parse_if_common, (void*)TypeData_parse_child, (void*)SyntaxTreeBranch_find_variable, (void*)TypeData_write_declaration, (void*)TypeData_write_methods_declaration, (void*)TypeData_write_global, (void*)TypeData_write_methods_body, (void*)TypeData_write_me};
#endif


#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct TypeWriter TypeWriter;
#elif LUMI_STAGE == LUMI_TYPES(0)
struct TypeWriter {
  Func* _dtl;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeWriter_write(TypeWriter* self, TypeData* type_data);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeWriter_write = "TypeWriter.write";
#define LUMI_FUNC_NAME _func_name_TypeWriter_write
Returncode TypeWriter_write(TypeWriter* self, TypeData* type_data) {
  RAISE(343)
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func TypeWriter__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func TypeWriter__dtl[] = {(void*)TypeWriter_write};
#endif

#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct TypeDeclarationWriter TypeDeclarationWriter;
#elif LUMI_STAGE == LUMI_TYPES(1)
struct TypeDeclarationWriter {
  TypeWriter _base;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeDeclarationWriter_write(TypeDeclarationWriter* self, TypeData* type_data);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeDeclarationWriter_write = "TypeDeclarationWriter.write";
#define LUMI_FUNC_NAME _func_name_TypeDeclarationWriter_write
Returncode TypeDeclarationWriter_write(TypeDeclarationWriter* self, TypeData* type_data) {
  CHECK(347, (type_data)->_base._base._base._dtl[8](type_data) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func TypeDeclarationWriter__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func TypeDeclarationWriter__dtl[] = {(void*)TypeDeclarationWriter_write};
#endif

#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct TypeMethodsDeclarationWriter TypeMethodsDeclarationWriter;
#elif LUMI_STAGE == LUMI_TYPES(1)
struct TypeMethodsDeclarationWriter {
  TypeWriter _base;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeMethodsDeclarationWriter_write(TypeMethodsDeclarationWriter* self, TypeData* type_data);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeMethodsDeclarationWriter_write = "TypeMethodsDeclarationWriter.write";
#define LUMI_FUNC_NAME _func_name_TypeMethodsDeclarationWriter_write
Returncode TypeMethodsDeclarationWriter_write(TypeMethodsDeclarationWriter* self, TypeData* type_data) {
  CHECK(351, (type_data)->_base._base._base._dtl[9](type_data) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func TypeMethodsDeclarationWriter__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func TypeMethodsDeclarationWriter__dtl[] = {(void*)TypeMethodsDeclarationWriter_write};
#endif

#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct TypeGlobalWriter TypeGlobalWriter;
#elif LUMI_STAGE == LUMI_TYPES(1)
struct TypeGlobalWriter {
  TypeWriter _base;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeGlobalWriter_write(TypeGlobalWriter* self, TypeData* type_data);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeGlobalWriter_write = "TypeGlobalWriter.write";
#define LUMI_FUNC_NAME _func_name_TypeGlobalWriter_write
Returncode TypeGlobalWriter_write(TypeGlobalWriter* self, TypeData* type_data) {
  CHECK(355, (type_data)->_base._base._base._dtl[10](type_data) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func TypeGlobalWriter__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func TypeGlobalWriter__dtl[] = {(void*)TypeGlobalWriter_write};
#endif

#if LUMI_STAGE == LUMI_TYPEDEFS
typedef struct TypeMethodsBodyWriter TypeMethodsBodyWriter;
#elif LUMI_STAGE == LUMI_TYPES(1)
struct TypeMethodsBodyWriter {
  TypeWriter _base;
};
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode TypeMethodsBodyWriter_write(TypeMethodsBodyWriter* self, TypeData* type_data);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_TypeMethodsBodyWriter_write = "TypeMethodsBodyWriter.write";
#define LUMI_FUNC_NAME _func_name_TypeMethodsBodyWriter_write
Returncode TypeMethodsBodyWriter_write(TypeMethodsBodyWriter* self, TypeData* type_data) {
  CHECK(359, (type_data)->_base._base._base._dtl[11](type_data) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif
#if LUMI_STAGE == LUMI_DECLARATIONS
extern Func TypeMethodsBodyWriter__dtl[];
#endif
#if LUMI_STAGE == LUMI_FUNCTIONS
Func TypeMethodsBodyWriter__dtl[] = {(void*)TypeMethodsBodyWriter_write};
#endif

#undef LUMI_FILE_NAME

#ifndef LUMI_INCLUDES
#define LUMI_INCLUDES
#include "tl4-compiler.c"
#include "global/argument.c"
#include "global/common.c"
#include "global/file-io.c"
#include "global/global.c"
#include "global/list.c"
#include "global/map.c"
#include "global/type-instance.c"
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
#include "syntax-tree/node.c"
#include "syntax-tree/root.c"
#include "statement/enum.c"
#include "statement/error.c"
#include "statement/for.c"
#include "statement/function.c"
#include "statement/native.c"
#include "statement/test.c"
#include "statement/variable.c"
#if LUMI_STAGE == LUMI_TYPES(1)
#undef LUMI_STAGE
#define LUMI_STAGE LUMI_TYPES(2)
#elif LUMI_STAGE == LUMI_TYPES(2)
#undef LUMI_STAGE
#define LUMI_STAGE LUMI_TYPES(3)
#elif LUMI_STAGE == LUMI_TYPES(3)
#undef LUMI_STAGE
#define LUMI_STAGE LUMI_TYPES(4)
#elif LUMI_STAGE == LUMI_TYPES(4)
#undef LUMI_STAGE
#define LUMI_STAGE LUMI_TYPES(5)
#endif
#undef LUMI_INCLUDES
#endif

#endif