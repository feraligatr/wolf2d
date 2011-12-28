#!/usr/bin/env python

class DataType:
	pass

class DataTypeInt(DataType):
	pass

class DataTypeString(DataType):
	pass

class DataTypeStringFixed(DataType):
	def __init__(self, size):
		self.size = size

class DataTypeMessage(DataType):
	def __init__(self, name, members):
		self.name = name
		self.members = members

class DataTypeStruct(DataType):
	def __init__(self, name, members):
		self.name = name
		self.members = members

class DataTypeStructRef(DataType):
	def __init__(self, src_struct):
		self.src = src_struct

class DataMember:
	def __init__(self, type, name):
		self.type = type
		self.name = name

import ply.lex

class MsgLexer:
	states = (
		('comment1', 'exclusive'),
		('comment2', 'exclusive'),
	)

	tokens = (
		#keywords
		"MESSAGE",
		"STRUCT",
		"INT",
		"STRING",

		#symbols
		"SEMICOLON",
		"LPAREN",
		"RPAREN",
		"LBRACE",
		"RBRACE",
		"LBRACK",
		"RBRACK",

		#tokens
		"NUMBER",
		"IDENTIFIER",
	)

	reserved = {
		'message' : 'MESSAGE',
		'struct' : 'STRUCT',
		'int' : 'INT',
		'string' : 'STRING',
	}

	def t_COMMENT1START(self, t):
		r'/\*'
		t.lexer.begin('comment1')

	def t_comment1_COMMENT1END(self, t):
		r'\*/'
		t.lexer.begin('INITIAL')

	t_comment1_ignore_ANYCHAR = r'.|\n'

	def t_comment1_error(self, t):
		self.t_error(t)

	def t_COMMENT2START(self, t):
		r'//'
		t.lexer.begin('comment2')

	def t_comment2_COMMENT2END(self, t):
		r'\n'
		t.lexer.begin('INITIAL')

	t_comment2_ignore_ANYCHAR = r'.'

	def t_comment2_error(self, t):
		self.t_error(t)

	t_SEMICOLON = ';'
	t_LPAREN = '\('
	t_RPAREN = '\)'
	t_LBRACE = '{'
	t_RBRACE = '}'
	t_LBRACK = '\['
	t_RBRACK = '\]'

	t_NUMBER = r'\d+'

	def t_IDENTIFIER(self, t):
		r'[a-zA-Z_][a-zA-Z_0-9]*'
		t.type = self.reserved.get(t.value, 'IDENTIFIER')
		return t

	t_ignore_SPACE = r'\s'

	def t_error(self, t):
		print "Illegal character '%s'" % t.value[0]
		t.lexer.skip(1)

	def build(self, **kwargs):
		self.lexer = ply.lex.lex(module=self, **kwargs)

	def test(self, data):
		self.lexer.input(data)
		while True:
			tok = self.lexer.token()
			if not tok: break
			print tok

class MsgParser:
	from ply import yacc
	def __init__(self):
		self.type_list = {}

	def p_declaration(self, p):
		''' declaration : struct
		                | message
		'''
		pass

	def p_struct(self, p):
		''' struct : STRUCT IDENTIFIER LBRACE vardecls RBRACE SEMICOLON
		'''
		p[0] = DataTypeStruct(p[2], p[4])
		self.type_list[p[2]] = p[0]

	def p_message(self, p):
		''' message : MESSAGE IDENTIFIER LBRACE vardecls RBRACE SEMICOLON
		'''
		p[0] = DataTypeMessage(p[2], p[4])
		self.type_list[p[2]] = p[0]
		print p[0]

	def p_vardecls(self, p):
		''' vardecls : vardecls vardecl
		'''
		p[0] = p[1] + [p[2]]

	def p_vardecls_new(self, p):
		''' vardecls : vardecl
		'''
		p[0] = [p[1]]

	def p_vardecl_int(self, p):
		''' vardecl : INT IDENTIFIER SEMICOLON
		'''
		p[0] = DataMember(DataTypeInt(), p[2])

	def p_vardecl_string(self, p):
		''' vardecl : STRING IDENTIFIER SEMICOLON
		'''
		p[0] = DataMember(DataTypeString(), p[2])

	def p_vardecl_string_fixed(self, p):
		''' vardecl : STRING LBRACK NUMBER RBRACK IDENTIFIER SEMICOLON
		'''
		p[0] = DataMember(DataTypeStringFixed(p[3]), p[5])

	def p_vardecl_struct_ref(self, p):
		''' vardecl : STRUCT IDENTIFIER IDENTIFIER SEMICOLON
		'''
		p[0] = DataMember(DataTypeStructRef(self.type_list[p[2]]), p[3])

	def p_error(self, p):
		print 'parser error'

	def build(self, **kwargs):
		self.lexer = MsgLexer()
		self.lexer.build(**kwargs)
		self.tokens = self.lexer.tokens
		self.parser = ply.yacc.yacc(module=self, **kwargs)

	def test(self, data):
		self.parser.parse(data, lexer = self.lexer.lexer)

import logging
logging.basicConfig(
    level = logging.DEBUG,
    filename = "parselog.txt",
    filemode = "w",
    format = "%(filename)10s:%(lineno)4d:%(message)s"
)
log = logging.getLogger()

m = MsgParser()
m.build(debug=True, debuglog=log)
testprog = """
/*
 * This is test comment
 */
message sample { // This is test
	int a;
};

"""
m.test(testprog)
