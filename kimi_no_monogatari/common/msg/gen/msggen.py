#!/usr/bin/env python

class DataType:
	pass

class DataTypeChar(DataType):
	def getCppType(self):
		return 'char'

class DataTypeInt(DataType):
	def getCppType(self):
		return 'int'

class DataTypeString(DataType):
	def getCppType(self):
		return 'const char *'

class DataTypeArray(DataType):
	def __init__(self, src_type, size):
		self.src = src_type
		self.size = size

class DataTypeMessage(DataType):
	def __init__(self, name, members):
		self.name = name
		self.members = members

	def getName(self):
		return self.name

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

	def getCppType(self):
		return self.type.getCppType()

	def getName(self):
		return self.name;

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
		"CHAR",
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
		'char' : 'CHAR',
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

	def p_declarations(self, p):
		''' declarations : declarations declaration
		                 | declaration
		'''
		pass

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
		self.addmsg_cb(p[0])

	def p_vardecls(self, p):
		''' vardecls : vardecls vardecl
		'''
		p[0] = p[1] + [p[2]]

	def p_vardecls_new(self, p):
		''' vardecls : vardecl
		'''
		p[0] = [p[1]]

	def p_vardecl(self, p):
		''' vardecl : datatype IDENTIFIER SEMICOLON
		'''
		p[0] = DataMember(p[1], p[2])

	def p_datatype_array(self, p):
		''' datatype : simple_datatype LBRACK NUMBER RBRACK
		'''
		p[0] = DataTypeArray(p[1], p[3])

	def p_datatype_simple(self, p):
		''' datatype : simple_datatype
		'''
		p[0] = p[1]

	def p_simple_datatype_char(self, p):
		''' simple_datatype : CHAR
		'''
		p[0] = DataTypeChar()

	def p_simple_datatype_int(self, p):
		''' simple_datatype : INT
		'''
		p[0] = DataTypeInt()

	def p_simple_datatype_string(self, p):
		''' simple_datatype : STRING
		'''
		p[0] = DataTypeString()

	def p_simple_datatype_struct_ref(self, p):
		''' simple_datatype : STRUCT IDENTIFIER
		'''
		p[0] = DataTypeStructRef(self.type_list[p[2]])

	def p_error(self, p):
		print 'parser error'

	def build(self, **kwargs):
		self.lexer = MsgLexer()
		self.lexer.build(**kwargs)
		self.tokens = self.lexer.tokens
		self.parser = ply.yacc.yacc(module=self, **kwargs)

	def test(self, data, addmsg_cb):
		self.addmsg_cb = addmsg_cb
		self.parser.parse(data, lexer = self.lexer.lexer)

def convert(def_file, template_file, output_file, log_file = 'parselog.txt'):
	import logging
	logging.basicConfig(
		level = logging.DEBUG,
		filename = log_file,
		filemode = "w",
		format = "%(filename)10s:%(lineno)4d:%(message)s"
	)
	log = logging.getLogger()

	m = MsgParser()
	m.build(debug=True, debuglog=log)
	msg_list = []
	with open(def_file, 'r') as f:
		m.test(f.read(), lambda msg: msg_list.append(msg))
	print msg_list

	import mako.template
	h_tmpl = mako.template.Template(filename=template_file)
	with open(output_file, 'w') as f:
		f.write(h_tmpl.render(msg_list=msg_list))

def main(argv):
	convert(def_file = 'messages.def', template_file = 'MessageParsers.h.tmpl', output_file = 'MessageParsers.h')

import sys

if __name__ == "__main__":
	sys.exit(main(sys.argv))
