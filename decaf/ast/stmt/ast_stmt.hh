/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. *
 * pp2: You will need to add new expression and statement node c
 * classes for the additional grammar elements (Switch/Postfix)
 */


#ifndef _H_ast_stmt
#define _H_ast_stmt

#include <ast/stmt/program.hh>
#include <ast/stmt/stmt.hh>
#include <ast/stmt/stmt_block.hh>
#include <ast/stmt/conditional_stmt.hh>
#include <ast/stmt/loop_stmt.hh>
#include <ast/stmt/for_stmt.hh>
#include <ast/stmt/while_stmt.hh>
#include <ast/stmt/if_stmt.hh>
#include <ast/stmt/break_stmt.hh>
#include <ast/stmt/case_stmt.hh>
#include <ast/stmt/default_stmt.hh>
#include <ast/stmt/switch_stmt.hh>
#include <ast/stmt/return_stmt.hh>
#include <ast/stmt/print_stmt.hh>

#endif
