#include"ErrorState.h"

namespace AMA
{
   ErrorState::ErrorState(const char * errorMessage)
   {
      if (errorMessage == nullptr)
      {
         messageError = nullptr;
      }
      else
      {
         messageError = new char[strlen(errorMessage) + 1];
         strcpy(messageError, errorMessage);
      }
   }
   ErrorState::~ErrorState()
   {
      delete[] messageError;
   }
   void ErrorState::clear()
   {
      if (!isClear())
      {
         delete[] messageError;
         messageError = nullptr;
      }
   }
   bool ErrorState::isClear() const
   {
      return (messageError == nullptr);
   }
   void ErrorState::message(const char * str)
   {
      delete[] messageError;
      messageError = new char[strlen(str) + 1];
      strcpy(messageError, str);
   }
   const char * ErrorState::message() const
   {
      return (this->messageError);
   }
   std::ostream& operator<<(std::ostream& os, const ErrorState& errorObj)
   {
      if (!errorObj.isClear())
      {
         os << errorObj.message();
      }
      return os;
   }
}