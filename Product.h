#define _CRT_SECURE_NO_WARNINGS
#ifndef _PRODUCT_H_
#define _PRODUCT_H_
#include<iostream>
#include<iomanip>
#include<cstring>
#include<string>
#include<fstream>
#include<sstream>
#include<ios>
#include"ErrorState.h"
#include"iProduct.h"

namespace AMA
{
   const int max_sku_length = 7;
   const int max_unit_length = 10;
   const int max_name_length = 75;
   const double TAX_RATE = 0.13;

   class Product: public iProduct
   {
   protected:
      void name(const char* recName);
      const char* name() const;
      double cost() const;
      void message(const char* recErrorState);
      bool isClear() const;
      const char* sku() const;
      char name();
      const char* unit() const;
      bool taxed() const;
      double price() const;

   public:
      Product(char recType = 'N');
      Product(const char* recSku, const char* recName, const char* recUnit, int recqty = 0, bool recTax = true,
         double recProdPrice = 0.0, int recQtyNeeded = 0);
      Product(const Product& src);
      Product operator=(const Product& src);
      ~Product();

      std::fstream& store(std::fstream& file, bool newLine = true) const;
      std::fstream& load(std::fstream& file);
      std::ostream& write(std::ostream& os, bool linear = true) const;
      std::istream& read(std::istream&is);
      bool operator==(const char* recSku) const;
      double total_cost() const;
      void quantity(int recNumUnitInHands);
      bool isEmpty() const;
      int qtyNeeded() const;
      int quantity() const;
      bool operator> (const char* recSku) const;
      bool operator> (const iProduct& recProduct) const;
      int operator+= (int addOrRemoveItem);
      void setProError(const char *str);

   private:
      char skuData[max_sku_length + 1];
      char productDescriptiion[max_unit_length + 1];
      char* pProdName;
      int qtyInHand;
      int qtyNeededData;
      double priceData;
      bool tax;

   protected:
      ErrorState ProdErrorState;
      char type;

   };
   std::ostream& operator<<(std::ostream& os, const iProduct& recProduct);
   std::istream& operator>>(std::istream& is, iProduct& recProduct);
   double operator+=(double& recDouble, const iProduct& recProduct);
}

#endif // !_PRODUCT_H_
