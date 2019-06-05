// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include "Date.h"
#include<string.h>

namespace AMA
{

   // number of days in month mon_ and year year_
   //
   int Date::mdays(int mon, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int month = mon >= 1 && mon <= 12 ? mon : 13;
      month--;
      return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }


   void Date::errCode(int errorCode)
   {
      erroCode = errorCode;
   }

   int Date::errCode() const
   {
      return (erroCode);
   }

   Date::Date()
   {
      setEmpty();
   }

   Date::Date(int receYear, int receMonth, int receDay)
   {
      if (receYear > max_year || receYear < min_year)
      {
         setEmpty();
         erroCode = YEAR_ERROR;
      }
      else if (receMonth < 1 || receMonth >12)
      {
         setEmpty();
         erroCode = MON_ERROR;
      }
      else if (receDay < 1 || receDay > mdays(receMonth, receYear))
      {
         setEmpty();
         erroCode = DAY_ERROR;
      }
      else
      {
         day = receDay;
         month = receMonth;
         year = receYear;
         setComparator();
         erroCode = NO_ERROR;
      }
   }

   Date::Date(const Date & src)
   {
      *this = src;
   }

   Date Date::operator=(const Date & src)
   {
      if (compa != src.compa)
      {
         day = src.day;
         month = src.month;
         year = src.year;
         compa = src.compa;
         erroCode = src.erroCode;
      }
      return Date();
   }

   void Date::setEmpty()
   {
      day = 0;
      month = 0;
      year = 0;
      erroCode = NO_ERROR;
      setComparator();
   }

   void Date::setComparator()
   {
      compa = year * 372 + month * 13 + day;
   }


   bool Date::operator==(const Date & rhs) const
   {
      return (this->compa != 0 && this->compa == rhs.compa);
   }

   bool Date::operator!=(const Date & rhs) const
   {
      return (this->compa != 0 && this->compa != rhs.compa);
   }

   bool Date::operator<(const Date & rhs) const
   {
      return (this->compa != 0 && this->compa < rhs.compa);
   }

   bool Date::operator>(const Date & rhs) const
   {
      return (this->compa != 0 && this->compa > rhs.compa);
   }

   bool Date::operator<=(const Date & rhs) const
   {
      return (this->compa != 0 && this->compa <= rhs.compa);
   }

   bool Date::operator>=(const Date & rhs) const
   {
      return (this->compa != 0 && this->compa >= rhs.compa);
   }


   std::istream & Date::read(std::istream & istr)
   {
      char holder;
      char holder2;
      istr >> year >> holder >> month >> holder2 >> day;
      setComparator();
      if (!istr.fail())
      {
         if (holder == '-' || holder == '/' || holder == '-' || holder == '/')
         {
            if (year > max_year || year < min_year)
            {
               setEmpty();
               erroCode = YEAR_ERROR;
            }
            else if (month < 1 || month >12)
            {
               setEmpty();
               erroCode = MON_ERROR;
            }
            else if (day < 1 || day > mdays(month, year))
            {
               setEmpty();
               erroCode = DAY_ERROR;
            }
            else
            {
               erroCode = NO_ERROR;
            }
         }
         else
         {
            setEmpty();
         }
      }
      else
      {
         setEmpty();
         erroCode = CIN_FAILED;
      }
      return istr;
   }

   std::ostream & Date::write(std::ostream & ostr, const Date& rhs) const
   {
      ostr.fill('0');
      ostr << rhs.year << "/";
      ostr.width(2);
      ostr << rhs.month << "/";
      ostr.width(2);
      ostr << rhs.day;
      ostr.fill(' ');
      return(ostr);
   }



   std::ostream & operator<<(std::ostream & ostr, const Date & rhs)
   {
      rhs.write(ostr, rhs);
      return (ostr);
   }

   std::istream & operator>>(std::istream & istr, Date & rhs)
   {
      rhs.read(istr);
      return (istr);
   }

}
