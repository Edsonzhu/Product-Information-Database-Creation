#ifndef AMA_DATE_H
#define AMA_DATE_H
#include<iostream>

const int min_year = 2000;
const int max_year = 2030;
const int NO_ERROR = 0;
const int CIN_FAILED = 1;
const int YEAR_ERROR = 2;
const int MON_ERROR = 3;
const int DAY_ERROR = 4;

namespace AMA {

   class Date {
      int day;
      int month;
      int year;
      int compa;
      int erroCode;
      int mdays(int, int)const;

   public:
      Date();
      Date(int receYear, int receMonth, int receDay);
      Date(const Date& src);
      Date operator=(const Date& src);

      void errCode(int errorCode);
      int errCode() const;
      void setEmpty();
      void setComparator();
      bool operator==(const Date& rhs) const;
      bool operator!=(const Date& rhs) const;
      bool operator<(const Date& rhs) const;
      bool operator>(const Date& rhs) const;
      bool operator<=(const Date& rhs) const;
      bool operator>=(const Date& rhs) const;


      std::istream& read(std::istream& istr);
      std::ostream& write(std::ostream& ostr, const Date& rhs) const;
   };

   std::ostream& operator<<(std::ostream& ostr, const Date& rhs); //cout
   std::istream& operator>>(std::istream& istr, Date& rhs); //cin




}
#endif