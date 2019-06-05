#define _CRT_SECURE_NO_WARNINGS
#ifndef _ERROR_H_
#define _ERROR_H_
#include<iostream>
#include<cstring>

namespace AMA
{
   class ErrorState
   {
   public:
      explicit ErrorState(const char* errorMessage = nullptr);
      ErrorState(const ErrorState& em) = delete;
      ErrorState& operator=(const ErrorState& em) = delete;
      virtual ~ErrorState();

      void clear();
      bool isClear() const;
      void message(const char* str);
      const char* message() const;

   private:
      char* messageError;
   };
   std::ostream& operator<<(std::ostream& os, const ErrorState& errorObj);
}

#endif // !_ERROR_H_
