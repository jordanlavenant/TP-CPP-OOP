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
      check(text.find("<svg width=\"100\" height=\"200\">") != std::string::npos, "vérification de l'en-tête");
      
      // 1.2 (pendant la durée de vie de l'objet)
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
      check(text2.find("<svg width=\"900\" height=\"900\">") != std::string::npos, "vérification de l'en-tête de la feuille par défaut");
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

  if (failures == 0) { std::cout << "all checks passed\n"; }

  return failures == 0 ? 0 : 1;
}
