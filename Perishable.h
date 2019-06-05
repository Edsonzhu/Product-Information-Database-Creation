#ifndef _PERISHABLE_H
#define _PERISHABLE_H

#include"Product.h"
#include"Date.h"

namespace AMA
{
   class Perishable: public Product
   {
   private:
      Date date;
      
   public:
      Perishable(char type = 'P');

      std::fstream& store(std::fstream& file, bool newLine = true) const;
      std::fstream& load(std::fstream& file);
      std::ostream& write(std::ostream& os, bool linear) const;
      std::istream& read(std::istream& is);
      const Date& expiry() const;

   };
}

#endif // !_PERISHABLE_H
