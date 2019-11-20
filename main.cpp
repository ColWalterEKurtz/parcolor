// -----------------------------------------------------------------------------
// main.cpp                                                             main.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the program's showHelp(), showVersion()
 *             and main() function and doxygen's main page.
 * @author     Col. Walter E. Kurtz
 * @version    2019-11-20
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
#include <string>
#include <iostream>
#include "cli.h"
#include "LaTeXGenerator.h"


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
  cout << indent << "-i <N>  use at most <N> lines in the initial paragraph" << endl;
  cout << indent << "-p <N>  use at most <N> lines in each paragraph" << endl;
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
  cout << "2019-11-20" << endl;
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
      LaTeXGenerator generator;

      // initialize generator
      generator.setSyntaxCharacter(cmdl.synchar);
      generator.enableBackgroundColor(!cmdl.blank);
      generator.enableDocument(cmdl.document);
      generator.setMaxLinesFirst(cmdl.maxLinesInitial);
      generator.setMaxLinesEach(cmdl.maxLinesParagraph);

      // generate LaTeX code
      if ( !generator.parse() ) 
      {
        // signalize trouble
        return 1;
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
