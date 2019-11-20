// -----------------------------------------------------------------------------
// LaTeXGenerator.cpp                                         LaTeXGenerator.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref LaTeXGenerator class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-11-20
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <iostream>
#include "LaTeXGenerator.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// --------------
// LaTeXGenerator
// --------------
/*
 *
 */
LaTeXGenerator::LaTeXGenerator()
{
  m_trigger  = '!';
  m_bgcolor  = true;
  m_document = false;
  m_maxFirst = 0;
  m_maxEach  = 0;
  m_line     = "";
  m_parsed   = "";
  m_cc       = 0;
  m_rc       = 0;
}


// -----------------------------------------------------------------------------
// Initialization                                                 Initialization
// -----------------------------------------------------------------------------

// ------------------
// setSyntaxCharacter
// ------------------
/*
 *
 */
void LaTeXGenerator::setSyntaxCharacter(char trigger)
{
  m_trigger = trigger;
}

// ---------------------
// enableBackgroundColor
// ---------------------
/*
 *
 */
void LaTeXGenerator::enableBackgroundColor(bool flag)
{
  m_bgcolor = flag;
}

// --------------
// enableDocument
// --------------
/*
 *
 */
void LaTeXGenerator::enableDocument(bool flag)
{
  m_document = flag;
}

// ----------------
// setMaxLinesFirst
// ----------------
/*
 *
 */
void LaTeXGenerator::setMaxLinesFirst(unsigned max)
{
  m_maxFirst = max;
}

// ---------------
// setMaxLinesEach
// ---------------
/*
 *
 */
void LaTeXGenerator::setMaxLinesEach(unsigned max)
{
  m_maxEach = max;
}


// -----------------------------------------------------------------------------
// Handling                                                             Handling
// -----------------------------------------------------------------------------

// -----
// parse
// -----
/*
 *
 */
bool LaTeXGenerator::parse()
{
  // reset buffers
  m_line   = "";
  m_parsed = "";
  m_cc     = 0;
  m_rc     = 0;

  if (m_document) openDocument();

  openGroup();

  // lines per paragraph
  unsigned lpp = 0;

  // initial paragraph
  bool initial = true;

  // get all lines from stdin
  while ( readLine() )
  {
    // generate LaTeX code
    if ( !parseLine() )
    {
      // signalize trouble
      return false;
    }

    // check lines within initial paragraph
    if (initial && (m_maxFirst > 0))
    {
      if (lpp == m_maxFirst)
      {
        // don't break LaTeX line
        if (lpp > 0) cout << "%" << endl;

        closeGroup();

        cout << "\\par" << endl;

        openGroup();

        lpp = 0;

        initial = false;
      }
    }

    // check lines within each paragraph
    if (m_maxEach > 0)
    {
      if (lpp == m_maxEach)
      {
        // don't break LaTeX line
        if (lpp > 0) cout << "%" << endl;

        closeGroup();

        cout << "\\par" << endl;

        openGroup();

        lpp = 0;

        initial = false;
      }
    }


    // break recent line
    if (lpp > 0) cout << "\\\\{}%" << endl;

    // show LaTeX line
    cout << m_parsed;

    // increase line counter
    lpp += 1;
  }

  // don't break LaTeX line
  if (lpp > 0) cout << "%" << endl;

  closeGroup();

  if (m_document) closeDocument();

  // signalize success
  return true;
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// ------------
// openDocument
// ------------
/*
 *
 */
void LaTeXGenerator::openDocument() const
{
  cout << "\\documentclass" << endl;
  cout << "[" << endl;
  cout << "  draft    = true," << endl;
  cout << "  fontsize = 11pt," << endl;
  cout << "  parskip  = half-," << endl;
  cout << "  BCOR     = 0pt," << endl;
  cout << "  DIV      = 11," << endl;
  cout << "  ngerman," << endl;
  cout << "  dvipsnames" << endl;
  cout << "]" << endl;
  cout << "{scrartcl}" << endl;
  cout << endl;
  cout << "\\usepackage[utf8]{inputenc}" << endl;
  cout << "\\usepackage[T1]{fontenc}" << endl;
  cout << "\\usepackage{lmodern}" << endl;
  cout << "\\usepackage{babel}" << endl;
  cout << "\\usepackage{xcolor}" << endl;
  cout << endl;
  cout << "% ------------------------------------------------------------------------------" << endl;
  cout << "\\begin{document}" << endl;
  cout << "% ------------------------------------------------------------------------------" << endl;
  cout << "\\small" << endl;
}

// -------------
// closeDocument
// -------------
/*
 *
 */
void LaTeXGenerator::closeDocument() const
{
  cout << "% ------------------------------------------------------------------------------" << endl;
  cout << "\\end{document}" << endl;
  cout << "% ------------------------------------------------------------------------------" << endl;
}

// ---------
// openGroup
// ---------
/*
 *
 */
void LaTeXGenerator::openGroup() const
{
  // always open LaTeX paragraph
  cout << "\\begingroup" << endl;
  cout << "\\ttfamily" << endl;
  cout << "\\setbox100=\\hbox{(}%" << endl;
  cout << "\\dimen100=\\ht100" << endl;
  cout << "\\advance\\dimen100 by \\dp100" << endl;
  cout << "\\renewcommand{\\ }{\\hspace*{0.5em}}%" << endl;
  cout << "\\definecolor{R}{named}{Red}%" << endl;
  cout << "\\definecolor{G}{named}{ForestGreen}%" << endl;
  cout << "\\definecolor{B}{named}{Cerulean}%" << endl;
  cout << "\\definecolor{C}{named}{Cyan}%" << endl;
  cout << "\\definecolor{M}{named}{Magenta}%" << endl;
  cout << "\\definecolor{Y}{named}{YellowOrange}%" << endl;

  // use background color (\colorbox)
  if (m_bgcolor)
  {
    cout << "\\definecolor{background}{rgb}{0.82,0.82,0.92}%" << endl;
    cout << "\\dimen200=\\linewidth" << endl;
    cout << "\\advance\\dimen200 by -2\\fboxsep" << endl;
    cout << "\\colorbox{background}%" << endl;
    cout << "{%" << endl;
    cout << "\\parbox{\\dimen200}%" << endl;
    cout << "{%" << endl;
  }

  // no background color
  else
  {
    cout << "\\parbox{\\linewidth}%" << endl;
    cout << "{%" << endl;
  }
}

// ----------
// closeGroup
// ----------
/*
 *
 */
void LaTeXGenerator::closeGroup() const
{
  // always close \parbox
  cout << "}% <-- parbox" << endl;

  // close \colorbox
  if (m_bgcolor)
  {
    cout << "}% <-- colorbox" << endl;
  }

  // always close LaTeX group
  cout << "\\endgroup" << endl;
}

// --------
// readLine
// --------
/*
 *
 */
bool LaTeXGenerator::readLine()
{
  // reset buffer
  m_line = "";

  // initialize return value
  bool extracted = false;

  // a sequence of whitespace characters
  string blank = "";

  // get characters from stdin
  while ( cin.get(m_cc) )
  {
    // CR
    if (m_cc == 13)
    {
      // at least one byte extracted from stream
      extracted = true;

      // line finished
      break;
    }

    // LF
    else if (m_cc == 10)
    {
      // standalone LF
      if (m_rc != 13)
      {
        // at least one byte extracted from stream
        extracted = true;

        // line finished
        break;
      }
    }

    else
    {
      // at least one byte extracted from stream
      extracted = true;

      // TAB
      if (m_cc == 9)
      {
        // buffer whitespace character
        blank += m_cc;
      }

      // SPACE
      else if (m_cc == 32)
      {
        // buffer whitespace character
        blank += m_cc;
      }

      // regular characters
      else
      {
        // check buffer
        if ( !blank.empty() )
        {
          // append all buffered characters
          m_line.append(blank);

          // reset buffer
          blank = "";
        }

        // append current character
        m_line += m_cc;
      }
    }

    // update recent character
    m_rc = m_cc;
  }

  // signalize whether some data has been extracted or not
  return extracted;
}

// ---------
// parseLine
// ---------
/*
 *
 */
bool LaTeXGenerator::parseLine()
{
  // reset buffer
  m_parsed = "";

  // empty line extracted
  if ( m_line.empty() )
  {
    // display empty line
    m_parsed = "\\rule{0pt}{\\dimen100}";

    // signalize success
    return true;
  }

  // the parser's states
  enum
  {
    PLAINCODE,
    ENTERMARKUP,
    COLORNAME,
    COLORCODE,
    LEAVEMARKUP
  }
  context(PLAINCODE);

  // parse extracted line
  for(string::size_type i = 0; i < m_line.size(); i++)
  {
    // get current character
    const char& c = m_line[i];

    // PLAINCODE
    if (context == PLAINCODE)
    {
      // first markup character found
      if (c == m_trigger)
      {
        // next context
        context = ENTERMARKUP;
      }

      else
      {
        // append translated character
        m_parsed += translate(c);
      }
    }

    // ENTERMARKUP
    else if (context == ENTERMARKUP)
    {
      // second markup character found
      if (c == m_trigger)
      {
        // start color command
        m_parsed += "\\textcolor{";

        // next context
        context = COLORNAME;
      }

      // markup character only occurred once
      else
      {
        // encode first markup character
        m_parsed += translate(m_trigger);

        // encode current character
        m_parsed += translate(c);

        // back to previous context
        context = PLAINCODE;
      }
    }

    // COLORNAME
    else if (context == COLORNAME)
    {
      // color name completed
      if (c == m_trigger)
      {
        // extend color command
        m_parsed += "}{\\textbf{";

        // next context
        context = COLORCODE;
      }

      // read color name
      else
      {
        // don't translate color name
        m_parsed += c;
      }
    }

    // COLORCODE
    else if (context == COLORCODE)
    {
      // first markup character found
      if (c == m_trigger)
      {
        // next context
        context = LEAVEMARKUP;
      }

      else
      {
        // encode current character
        m_parsed += translate(c);
      }
    }

    // LEAVEMARKUP
    else if (context == LEAVEMARKUP)
    {
      // second markup character found
      if (c == m_trigger)
      {
        // close LaTeX commands (\textcolor and \textbf)
        m_parsed += "}}";

        // back to initial context
        context = PLAINCODE;
      }

      // markup character only occurred once
      else
      {
        // encode recent markup character
        m_parsed += translate(m_trigger);

        // encode current character
        m_parsed += translate(c);

        // back to previous context
        context = COLORCODE;
      }
    }
  }

  // check final state
  return (context == PLAINCODE);
}

// ---------
// translate
// ---------
/*
 *
 */
string LaTeXGenerator::translate(char c) const
{
  // translate these characters
  switch(c) 
  {
    case    0:
    case    1:
    case    2:
    case    3:
    case    4:
    case    5:
    case    6:
    case    7:
    case    8: return "[CTRL]";
    case    9: return "\\ \\ ";
    case   10:
    case   11:
    case   12:
    case   13:
    case   14:
    case   15:
    case   16:
    case   17:
    case   18:
    case   19:
    case   20:
    case   21:
    case   22:
    case   23:
    case   24:
    case   25:
    case   26:
    case   27:
    case   28:
    case   29:
    case   30:
    case   31: return "[CTRL]";
    case '\\': return "\\textbackslash{}";
    case  '~': return "\\textasciitilde{}";
    case  '"': return "\\grqq{}";
    case  '^': return "\\^{}";
    case  '{': return "\\{";
    case  '}': return "\\}";
    case  '&': return "\\&";
    case  '$': return "\\$";
    case  '%': return "\\%";
    case  '#': return "\\#";
    case  '_': return "\\_";
    case  '-': return "-{}";
    case  '<': return "<{}";
    case  '>': return ">{}";
    case  ' ': return "\\ ";
  }

  // identity map
  return string(1, c);
}

