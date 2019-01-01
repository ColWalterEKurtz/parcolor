// -----------------------------------------------------------------------------
// main.cpp                                                             main.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the program's showHelp(), showVersion()
 *             and main() function and doxygen's main page.
 * @author     Col. Walter E. Kurtz
 * @version    2018-11-18
 * @copyright  GNU General Public License - Version 3.0
 *
 * @mainpage
 *
 * @section issue What is the issue here?
 *   parcolor typesets small snippets of source code in LaTeX.
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <limits>
#include <map>
#include <string>
#include <iostream>
#include "message.h"
#include "cli.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Functions                                                           Functions
// -----------------------------------------------------------------------------

// --------
// showHelp
// --------
/**
 * @brief  This function shows the program's help.
 */
void showHelp(const cli& cmdl)
{
  const string indent("\t");

  cout << endl;
  cout << "NAME" << endl;
  cout << indent << "parcolor - colorized paragraph" << endl;
  cout << endl;
  cout << "SYNOPSIS" << endl;
  cout << indent << "parcolor [options]" << endl;
  cout << endl;
  cout << "OPTIONS" << endl;
  cout << indent << "-h      show this help screen and exit" << endl;
  cout << indent << "-v      show the program's version end exit" << endl;
  cout << indent << "-x      show an exemplary input file and exit" << endl;
  cout << indent << "-b      no background color" << endl;
  cout << indent << "-d      create complete tex file" << endl;
  cout << indent << "-c <S>  use <A> as caption" << endl;
  cout << indent << "-s <A>  use <A> as syntactic character ('" << cmdl.synchar << "' by default)" << endl;
  cout << endl;
  cout << "DESCRIPTION" << endl;
  cout << indent << "parcolor translates the passed input to LaTeX code." << endl;
  cout << indent << "Following sequences will be highlighted: !!COLOR!CODE!!" << endl;
  cout << indent << "All data is read from stdin and written to stdout." << endl;
  cout << endl;
}

// -----------
// showVersion
// -----------
/**
 * @brief  This function shows the program's version.
 */
void showVersion()
{
  cout << "2018-11-18" << endl;
}

// -----------
// showExample
// -----------
/**
 * @brief  This function shows a snippet of source code,
 *         that is supplemented with some highlight sequences.
 */
void showExample()
{
  cout << "!!G!% layout and global options!!" << endl;
  cout << "!!B!\\documentclass!!" << endl;
  cout << "[" << endl;
  cout << "  draft    = true," << endl;
  cout << "  fontsize = 11pt," << endl;
  cout << "  parskip  = half-," << endl;
  cout << "  BCOR     = 0pt," << endl;
  cout << "  DIV      = calc," << endl;
  cout << "  ngerman" << endl;
  cout << "]" << endl;
  cout << "{!!R!scrartcl!!}" << endl;
  cout << endl;
  cout << "!!G!% default packages!!" << endl;
  cout << "!!B!\\usepackage!![utf8]{inputenc}" << endl;
  cout << "!!B!\\usepackage!![T1]{fontenc}" << endl;
  cout << "!!B!\\usepackage!!{lmodern}" << endl;
  cout << "!!B!\\usepackage!!{babel}" << endl;
  cout << endl;
  cout << "!!G!% document!!" << endl;
  cout << "!!B!\\begin!!{!!R!document!!}" << endl;
  cout << "" << endl;
  cout << "!!B!\\section!!{Hello, World!}" << endl;
  cout << endl;
  cout << "!!B!\\end!!{!!R!document!!}" << endl;
}

// --------------------
// initializeTranslator
// --------------------
/**
 * @brief  This function defines which characters in the source code
 *         are to be replaced by LaTeX commands.
 */
void initializeTranslator(map<char, string>& translator)
{
  // reset
  translator.clear();

  const char max(numeric_limits<char>::max());
  const char min(-max - 1);

  // initialize map
  for(char c = min; c < max; c++)
  {
    translator[c] = string(1, c);
  }

  // initialize last element
  translator[max] = string(1, max);

  // translate all control characters
  for(char c = 0; c < 32; c++)
  {
    translator[c] = ("[CTRL]");
  }

  // translate these characters
  translator[9]    = "\\ \\ \\ ";
  translator[10]   = string(1, 10);
  translator[13]   = string(1, 13);
  translator['\\'] = "\\textbackslash{}";
  translator['~']  = "\\textasciitilde{}";
  translator['"']  = "\\grqq{}";
  translator['^']  = "\\^{}";
  translator['{']  = "\\{";
  translator['}']  = "\\}";
  translator['&']  = "\\&";
  translator['$']  = "\\$";
  translator['%']  = "\\%";
  translator['#']  = "\\#";
  translator['_']  = "\\_";
  translator['-']  = "-{}";
  translator['<']  = "<{}";
  translator['>']  = ">{}";
  translator[' ']  = "\\ ";
}

// ---------
// openGroup
// ---------
/**
 * @brief  This function pushes the LaTeX code to stdout,
 *         that precedes each source code section.
 */
void openGroup(bool blank, const string& caption)
{
  // always open LaTeX paragraph
  cout << "\\begingroup" << endl;
  cout << "\\ttfamily" << endl;
  cout << "\\renewcommand{\\ }{\\hspace*{0.5em}}%" << endl;
  cout << "\\definecolor{R}{named}{Red}%" << endl;
  cout << "\\definecolor{G}{named}{ForestGreen}%" << endl;
  cout << "\\definecolor{B}{named}{Cerulean}%" << endl;
  cout << "\\definecolor{C}{named}{Cyan}%" << endl;
  cout << "\\definecolor{M}{named}{Magenta}%" << endl;
  cout << "\\definecolor{Y}{named}{YellowOrange}%" << endl;

  // no background color
  if (blank)
  {
    cout << "\\parbox{\\linewidth}" << endl;
    cout << "{%" << endl;
  }

  // use background color (\colorbox)
  else
  {
    cout << "\\definecolor{background}{rgb}{0.82,0.82,0.92}%" << endl;
    cout << "\\dimen100=\\linewidth" << endl;
    cout << "\\advance\\dimen100 by -2\\fboxsep" << endl;
    cout << "\\colorbox{background}" << endl;
    cout << "{%" << endl;
    cout << "\\parbox{\\dimen100}" << endl;
    cout << "{%" << endl;
  }

  // set caption
  if ( !caption.empty() )
  {
    cout << "\\hfill\\fbox{\\textsf{" << caption << "}}\\\\" << endl;
  }
}

// ----------
// closeGroup
// ----------
/**
 * @brief  This function pushes the LaTeX code to stdout,
 *         that follows each source code section.
 */
void closeGroup(bool blank)
{
  // always close \parbox
  cout << "}%" << endl;

  // close \colorbox
  if (!blank)
  {
    cout << "}%" << endl;
  }

  // always close LaTeX group
  cout << "\\endgroup" << endl;
}

// ----------
// parseInput
// ----------
/**
 * @brief  This function translates the source code
 *         (from stdin) to LaTeX (and pushed it to stdout).
 */
void parseInput(char synchar)
{
  // create and initialize character map
  map<char, string> translator;
  initializeTranslator(translator);

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

  char rc(0);  // recent character
  char cc(0);  // current character

  // number of buffered new line characters
  int nlbuffer = 0;

  // read all characters from stdin
  while( cin.get(cc) )
  {
    // CR
    if (cc == 13)
    {
      // intro started
      if (context == ENTERMARKUP)
      {
        // encode markup character
        cout << translator[synchar];

        // back to previous context
        context = PLAINCODE;
      }

      // outro started
      else if (context == LEAVEMARKUP)
      {
        // encode markup character
        cout << translator[synchar];

        // back to previous context
        context = COLORCODE;
      }

      // step counter
      nlbuffer += 1;

      // update recent character
      rc = cc;

      // next cycle
      continue;
    }

    // LF
    if (cc == 10)
    {
      // stand-alone LF
      if (rc != 13)
      {
        // intro started
        if (context == ENTERMARKUP)
        {
          // encode markup character
          cout << translator[synchar];

          // back to previous context
          context = PLAINCODE;
        }

        // outro started
        else if (context == LEAVEMARKUP)
        {
          // encode markup character
          cout << translator[synchar];

          // back to previous context
          context = COLORCODE;
        }

        // step counter
        nlbuffer += 1;
      }

      // update recent character
      rc = cc;

      // next cycle
      continue;
    }

    // insert all buffered new line characters
    if (nlbuffer > 0)
    {
      for(int i = 0; i < nlbuffer; i++)
      {
        // insert LaTeX newline
        cout << "\\\\{}" << endl;
      }

      // reset counter
      nlbuffer = 0;
    }

    // PLAINCODE
    if (context == PLAINCODE)
    {
      // first markup character found
      if (cc == synchar)
      {
        // next context
        context = ENTERMARKUP;
      }

      else
      {
        cout << translator[cc];
      }
    }

    // ENTERMARKUP
    else if (context == ENTERMARKUP)
    {
      // second markup character found
      if (cc == synchar)
      {
        // start color command
        cout << "\\textcolor{";

        // next context
        context = COLORNAME;
      }

      // markup character only occurred once
      else
      {
        // encode first markup character
        cout << translator[synchar];

        // encode current character
        cout << translator[cc];

        // back to previous context
        context = PLAINCODE;
      }
    }

    // COLORNAME
    else if (context == COLORNAME)
    {
      // color name completed
      if (cc == synchar)
      {
        cout << "}{\\textbf{";
        context = COLORCODE;
      }

      // push color name to stdout
      else
      {
        // don't translate color name
        cout << cc;
      }
    }

    // COLORCODE
    else if (context == COLORCODE)
    {
      // first markup character found
      if (cc == synchar)
      {
        // next context
        context = LEAVEMARKUP;
      }

      else
      {
        // encode current character
        cout << translator[cc];
      }
    }

    // LEAVEMARKUP
    else if (context == LEAVEMARKUP)
    {
      // second markup character found
      if (cc == synchar)
      {
        // close LaTeX commands (\textcolor and \textbf)
        cout << "}}";

        // back to initial context
        context = PLAINCODE;
      }

      // markup character only occurred once
      else
      {
        // encode recent markup character
        cout << translator[synchar];

        // encode current character
        cout << translator[cc];

        // back to previous context
        context = COLORCODE;
      }
    }

    // update recent character
    rc = cc;
  }
}

// ----
// main
// ----
/**
 * @brief  The program starts in this function.
 *
 * @param argc  holds the number of passed command-line arguments.
 * @param argv  holds the list of passed command-line arguments.
 *
 * @return
 * Value | Meaning
 * ----: | :------
 *     0 | The requested operation finished successfully.
 *     1 | The requested operation failed.
 */
int main(int argc, char** argv)
{
  // create command-line parser
  cli cmdl;

  // parse command-line
  if ( cmdl.parse(argc, argv) )
  {
    // SHOW_HELP
    if (cmdl.operation == cli::SHOW_HELP)
    {
      showHelp(cmdl);
    }

    // SHOW_VERSION
    else if (cmdl.operation == cli::SHOW_VERSION)
    {
      showVersion();
    }

    // SHOW_EXAMPLE
    else if (cmdl.operation == cli::SHOW_EXAMPLE)
    {
      showExample();
    }

    // DEFAULT
    else if (cmdl.operation == cli::DEFAULT)
    {
      // start complete LaTeX document
      if (cmdl.document)
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
        cout << "\\pagestyle{empty}" << endl;
        cout << endl;
        cout << "\\begin{document}" << endl;
      }

      // start source code section
      openGroup(cmdl.blank, cmdl.caption);

      // parse input from stdin
      parseInput(cmdl.synchar);

      // finish source code section
      closeGroup(cmdl.blank);

      // close LaTeX document
      if (cmdl.document)
      {
        cout << "\\end{document}" << endl;
      }
    }
  }

  // invalid command-line
  else
  {
    // signalize trouble
    return 1;
  }

  // signalize success
  return 0;
}
