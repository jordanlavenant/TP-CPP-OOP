#include "canvas.hpp"
#include "color.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

static int failures = 0;

static void check(bool condition, char const* what)
{
  if (!condition) { std::cerr << "FAILED: " << what << '\n'; ++failures; }
}

// Whether one string appears before another. Both have to be there for the
// answer to mean anything, which is why the absent case counts as false.
static bool before(std::string const& text, char const* first, char const* second)
{
  std::size_t const a = text.find(first);
  std::size_t const b = text.find(second);
  return a != std::string::npos && b != std::string::npos && a < b;
}

int main()
{
  // ------------------------------------------------------------------ given

  {
    // Nothing has been built yet, so nothing is alive. This one passes from
    // the start, and it is the baseline the next checks are read against.
    check(canvas::alive() == 0, "no canvas exists before any is built");
  }

  // --------------------------------------------------------------- to write
  
  // Partie 1
  {
    std::ostringstream out;
    {
      // 1.1
      canvas feuille1(out, 100, 200);
      check(feuille1.width() == 100 && feuille1.height() == 200, "l'affichage est de la bonne taille");
      check(feuille1.centre().x == 50.0 && feuille1.centre().y == 100.0, "le centre est au bon endroit");
      std::string const text = out.str();
      check(text.find("<svg xmlns='http://www.w3.org/2000/svg' width=\"100\" height=\"200\">") != std::string::npos, "vérification de l'en-tête");
      
      // 1.2 (pendant que l'objet est en vie)
      check(text.find("</svg>") == std::string::npos, "vérification que la balise fermante est absente du flux");
    }
    // 1.2 (après destruction)
    std::string const text_after = out.str();
    check(text_after.find("</svg>") != std::string::npos, "vérification que la balise fermante est présente après destruction");
    {
      // 1.3
      canvas feuille2(out);
      check(feuille2.width() == 900 && feuille2.height() == 900, "la feuille par défaut est de 900 par 900");
      std::string const text2 = out.str();
      check(text2.find("<svg xmlns='http://www.w3.org/2000/svg' width=\"900\" height=\"900\">") != std::string::npos, "vérification de l'en-tête de la feuille par défaut");
    }
    // 1.5
    {
      std::ostringstream out_2;
    
      check(canvas::alive() == 0, "alive avant construction");
    
      canvas c1(out, 100, 100);
      {
        canvas c2(out_2, 200, 200);
        check(canvas::alive() == 2, "alive après seconde construction");
      }
    
      check(canvas::alive() == 1, "alive à la sortie de la portée interne");
    }
  }

  {
    // The checks the questions ask for go here. `before` above tells whether
    // one string appears before another in the text of a file.
    check(before("<svg></svg>", "<svg", "</svg>"), "before reads the order of two tags");
  }
  {
    // The delegating constructor does the same work as the other, once.
    std::ostringstream out;

    {
      canvas sheet(out);
      check(sheet.width() == 900 && sheet.height() == 900, "the default sheet is 900 by 900");
    }

    std::string const text = out.str();
    check(text.find("<svg") == text.rfind("<svg"),   "the header is written exactly once");
    check(text.find("</svg>") == text.rfind("</svg>"), "and so is the closing tag");
  }
  {
    // The stroke count is per object, unlike the live count.
    std::ostringstream out;
    canvas sheet(out, 100, 100);

    sheet.line({0.0, 0.0}, {1.0, 1.0}, color{255, 0, 0}, 1.0);
    sheet.line({1.0, 1.0}, {2.0, 2.0}, color{0, 255, 0}, 1.0);

    check(sheet.strokes() == 2, "two lines, counted by the canvas that drew them");
  }

  // ------------------------------------------------------------------ part 4
  {
    std::ostringstream out;
    try 
    {
      canvas feuille(out);
      group const g1(feuille, "");
      group const g2(feuille, "");

      throw std::runtime_error("test");
    }
    catch (std::runtime_error const&)
    {
    }

    std::string text = out.str();
    std::size_t g1_close = text.find("</g>");
    std::size_t g2_close = text.find("</g>", g1_close + 1);

    check(g1_close != std::string::npos, "la balise fermante du premier groupe existe");
    check(g2_close != std::string::npos, "la balise fermante du second groupe existe");
    
    std::size_t svg_close = text.find("</svg>");
    check(svg_close != std::string::npos, "la balise fermante du svg existe");
    
    check(canvas::alive() == 0, "canvas::alive() vaut 0");
  }

  if (failures == 0) { std::cout << "all checks passed\n"; }

  return failures == 0 ? 0 : 1;
}
