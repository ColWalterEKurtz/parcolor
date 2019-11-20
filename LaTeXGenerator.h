// -----------------------------------------------------------------------------
// LaTeXGenerator.h                                             LaTeXGenerator.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref LaTeXGenerator class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-11-20
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef LATEXGENERATOR_H_INCLUDE_NO1
#define LATEXGENERATOR_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>


// --------------
// LaTeXGenerator
// --------------
/**
 * @brief  The best class in the world.
 */
class LaTeXGenerator
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // --------------
  // LaTeXGenerator
  // --------------
  /**
   * @brief  The standard-constructor.
   */
  LaTeXGenerator();


  // ---------------------------------------------------------------------------
  // Initialization                                               Initialization
  // ---------------------------------------------------------------------------

  // ------------------
  // setSyntaxCharacter
  // ------------------
  /**
   * @brief  This method sets ! in the !!COLOR!CODE!! sequence.
   */
  void setSyntaxCharacter(char trigger);

  // ---------------------
  // enableBackgroundColor
  // ---------------------
  /**
   * @brief  This method defines whether to use the background color or not.
   */
  void enableBackgroundColor(bool flag);

  // --------------
  // enableDocument
  // --------------
  /**
   * @brief  This method defines whether to create a full LaTeX file or not.
   */
  void enableDocument(bool flag);

  // ----------------
  // setMaxLinesFirst
  // ----------------
  /**
   * @brief  This method sets the maximum number of lines within the initial paragraph.
   */
  void setMaxLinesFirst(unsigned max);

  // ---------------
  // setMaxLinesEach
  // ---------------
  /**
   * @brief  This method sets the maximum number of lines within each paragraph.
   */
  void setMaxLinesEach(unsigned max);


  // ---------------------------------------------------------------------------
  // Handling                                                           Handling
  // ---------------------------------------------------------------------------

  // -----
  // parse
  // -----
  /**
   * @brief  This method parses the code from stdin.
   */
  bool parse();


protected:

  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // ------------
  // openDocument
  // ------------
  /**
   * @brief  This method starts a complete LaTeX file.
   */
  void openDocument() const;

  // -------------
  // closeDocument
  // -------------
  /**
   * @brief  This method finishes a complete LaTeX file.
   */
  void closeDocument() const;

  // ---------
  // openGroup
  // ---------
  /**
   * @brief  This method starts a colored paragraph.
   */
  void openGroup() const;

  // ----------
  // closeGroup
  // ----------
  /**
   * @brief  This method finishes a colored paragraph.
   */
  void closeGroup() const;

  // --------
  // readLine
  // --------
  /**
   * @brief  This method extracts one line from stdin.
   */
  bool readLine();

  // ---------
  // parseLine
  // ---------
  /**
   * @brief  This method creates the LaTeX code that displays the extracted line.
   */
  bool parseLine();

  // ---------
  // translate
  // ---------
  /**
   * @brief  This method translates the given character to printable LaTeX code.
   */
  std::string translate(char c) const;


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the trigger character
  char m_trigger;

  /// use background color or not
  bool m_bgcolor;

  /// create complete tex file or not
  bool m_document;

  /// maximum number of lines in the initial paragraph
  unsigned m_maxFirst;

  /// maximum number of lines in each paragraph
  unsigned m_maxEach;

  /// the currently extracted line
  std::string m_line;

  /// the currently parsed line
  std::string m_parsed;

  /// the currently extracted character
  char m_cc;

  /// the recently extracted character
  char m_rc;

};

#endif  /* #ifndef LATEXGENERATOR_H_INCLUDE_NO1 */

