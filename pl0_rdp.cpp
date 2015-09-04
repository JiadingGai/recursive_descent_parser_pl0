#include <iostream>
#include <string>
typedef enum {
  tok_eof = 5,
  ident,
  number,
  lparen,
  rparen,
  times,
  slash,
  plus,
  minus,
  eql,
  neq,
  lss,
  leq,
  gtr,
  geq,
  callsym,
  beginsym,
  semicolon,
  endsym,
  ifsym,
  whilesym,
  becomes,
  thensym,
  dosym,
  constsym,
  dosym,
  constsym,
  comma,
  varsym,
  procsym,
  period,
  oddsym,
  exclamationsym,
  questionsym
} Symbol;

Symbol sym;
void nextsym(void);
void error(const char *msg);
void block(void);
void statement(void);
void condition(void);
void term(void);
void factor(void);
void expression(void);
void expect(Symbol s);
void accept(Symbol s);
void program(void);

static std::string IdentifierStr;
static double NumVal;
