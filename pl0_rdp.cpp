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
int expect(Symbol s);
int accept(Symbol s);
void program(void);

static std::string IdentifierStr;
static double NumVal;

static int gettok()
{
  static int LastChar = ' ';

  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (isalnum(LastChar = getchar())) {
      IdentifierStr += LastChar;
    }

#if _DEBUG
    printf("[IdentifierStr] %s (followed by %c)\n", IdentifierStr.c_str(), LastChar);
#endif

    if (IdentifierStr == "call") return callsym;
    if (IdentifierStr == "begin") return beginsym;
    if (IdentifierStr == "end") return endsym;
    if (IdentifierStr == "if") return ifsym;
    if (IdentifierStr == "while") return whilesym;
    if (IdentifierStr == "then") return thensym;
    if (IdentifierStr == "do") return dosym;
    if (IdentifierStr == "const") return constsym;
    if (IdentifierStr == "var") return varsym;
    if (IdentifierStr == "procedure") return procsym;
    if (IdentifierStr == "odd") return oddsym;

    return ident;
  }

  //FIXME: not able to recognize numbers like .12345.
  //       because of the conflict with program period.
  if (isdigit(LastChar)/* || LastChar == '.'*/) {
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), 0);
    return number;
  }

  if (LastChar == EOF)
    return tok_eof;

  if (LastChar == '*') {
    LastChar = getchar();
    return times;
  }

  if (LastChar == ',') {
    LastChar = getchar();
    return comma;
  }

  if (LastChar == '!') {
    LastChar = getchar();
    return exclamationsym;
  }

  if (LastChar == '?') {
    LastChar = getchar();
    return questionsym;
  }

  if (LastChar == ';') {
    LastChar = getchar();
    return semicolon;
  }

  if (LastChar == '+') {
    LastChar = getchar();
    return plus;
  }

  if (LastChar == '.') {
    return period;
  }

  if (LastChar == ':') {
    LastChar = getchar();
    if (LastChar == '=') {
      LastChar = getchar();
      return becomes;
    }
  }

  if (LastChar == '<') {
    LastChar = getchar();
    if (LastChar == '=') {
      LastChar = getchar();
      return leq;
    }
  }

  int ThisChar = getchar();
  LastChar = getchar();
  return ThisChar;
}

int main(void)
{
  program();
  printf("PARSE SUCCESS.\n");
  return 0;
}

static int CurTok;
void nextsym(void)
{
  CurTok = gettok();
  sym = static_cast<Symbol>(CurTok);

#if _DEBUG
  printf("[CurrentSymbol] %d\n", sym);
#endif
}

void program(void)
{
  nextsym();
  block();
  expect(period);
}

void block(void)
{
  if (accept(constsym)) {
    do {
      expect(ident);
      expect(eql);
      expect(number);
    } while (accept(comma));

    expect(semicolon);
  }
  
  if (accept(varsym)) {
    do {
      expect(ident);
    } while (accept(comma));

    expect(semicolon);
  }

  while (accept(procsym)) {
    expect(ident);
    expect(semicolon);
    block();
    expect(semicolon);
  }
  
  statement();
}

void statement(void)
{
  if (accept(ident)) {
    expect(becomes);
    expression(); 
  } else if (accept(callsym)) {
    expect(ident);
  } else if (accept(exclamationsym)) {
    expect(ident);
  } else if (accept(questionsym)) {
    expression();
  } else if (accept(beginsym)) {
    do {
      statement();
    } while (accept(semicolon));
    expect(endsym);
  } else if (accept(ifsym)) {
    condition();
    expect(thensym);
    statement();
  } else if (accept(whilesym)) {
    condition();
    expect(dosym);
    statement();
  } else {
    error("STATEMENT: syntax error in void statement(void).\n");
    nextsym();
  }
}

void condition(void)
{
  if (accept(oddsym)) {
    expression();
  } else {
    expression();
    if (sym == eql || sym == neq || sym == lss || sym == leq || sym == gtr || sym == geq) {
      nextsym();
      expression();
    } else {
      error("CONDITION: invalid operator in void condition(void).");
      nextsym();
    }
  }
}

void expression(void)
{
  if (sym == plus || sym == minus) {
    nextsym();
  }
  term();

  while (sym == plus || sym == minus) {
    nextsym();
    term();
  }
}

void term(void)
{
  factor();
  while (sym == times || sym == slash) {
    nextsym();
    factor();
  }
}

void factor(void)
{
  if (accept(ident)) {
    ;
  } else if (accept(number)) {
    ;
  } else if (accept(lparen)) {
    nextsym();
    expression();
    expect(rparen);
  } else {
    error("FACTOR: syntax error in void factor(void).");
    nextsym();
  }
}

int expect(Symbol s)
{
  if (accept(s)) {
    return 1;
  }

  printf("\n     [%d(%c), but expects %d(%c)]\n", sym, sym, s, s);
  error("[Expect] unexpected symbol.");
  return 0;
}

int accept(Symbol s)
{
  if (sym == s) {
    nextsym();
    return 1;
  }

  return 0;
}

void error(const char *msg)
{
  printf("ERROR: %s at %s:%d\n", msg, __FILE__, __LINE__);
  exit(1);
}
