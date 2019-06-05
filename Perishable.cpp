#include"Perishable.h"

namespace AMA
{
   Perishable::Perishable(char type/* = 'P'*/) : Product(type) {}

   std::fstream & Perishable::store(std::fstream & file, bool newLine/* = true*/) const
   {
      Product::store(file, false);
      file << ',' << date;
      if (newLine)
      {
         file << std::endl;
      }
      return(file);
   }

   std::fstream & Perishable::load(std::fstream & file)
   {
      Product::load(file);
      std::string str;

      std::getline(file, str);
      //std::stringstream inputHolder(str);
      
      //inputHolder >> this->date;
      date.read(file);
      return (file);
   }

   std::ostream & Perishable::write(std::ostream & os, bool linear) const
   {
      Product::write(os, linear);
      if (ProdErrorState.isClear())
      {
         if (linear)
         {
            os << expiry();
         }
         else
         {
            os << " Expiry date: " << expiry();
         }
      }
      return (os);
   }

   std::istream & Perishable::read(std::istream & is)
   {
      if (!Product::read(is).fail())
      {
         Date dateHolder;
         std::cout << " Expiry date (YYYY/MM/DD): ";
         is >> dateHolder;

         if (dateHolder.errCode() != NO_ERROR)
         {
            is.setstate(std::ios::failbit);
            switch (dateHolder.errCode())
            {
            case 1:
               Product::setProError("Invalid Date Entry");
               break;
            case 2:
               Product::setProError("Invalid Year in Date Entry");
               break;
            case 3:
               Product::setProError("Invalid Month in Date Entry");
               break;
            case 4:
               Product::setProError("Invalid Day in Date Entry");
               break;
            default:
               break;
            }
         }
         else
         {
            //Product::ProdErrorState.clear();
            this->date = dateHolder;
         }
         /*if (type != 'P')
         {
            type = 'P';
         }*/
      }
      return (is);
   }

   const Date & Perishable::expiry() const
   {
      return (date);
   }
}