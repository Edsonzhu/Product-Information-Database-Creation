#include "Product.h"

// Final Project Milestone 3
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
// Name   Edson Zhu       Date                 Reason
/////////////////////////////////////////////////////////////////

namespace AMA
{
   void Product::name(const char* recName)
   {
      if (recName == nullptr)
      {
         pProdName = nullptr;
      }
      else
      {
         pProdName = new char[strlen(recName) + 1];
         strcpy(pProdName, recName);
      }
   }

   const char* Product::name() const
   {
      return (pProdName == nullptr ? nullptr : pProdName);
   }

   const char* Product::unit() const
   {
      return (productDescriptiion);
   }

   bool Product::taxed() const
   {
      return (tax);
   }

   double Product::price() const
   {
      return (priceData);
   }

   double Product::cost() const
   {
      return (tax ? priceData * TAX_RATE : priceData);
   }

   void Product::message(const char* recErrorState)
   {
      ProdErrorState.message(recErrorState);
   }

   bool Product::isClear() const
   {
      return (ProdErrorState.isClear());
   }

   Product::Product(char recType)
   {
      type = recType;
      name(nullptr);
      skuData[0] = '\0';
      productDescriptiion[0] = '\0';
      qtyInHand = 0;
      qtyNeededData = 0;
      priceData = 0.0;
      tax = false;
      ProdErrorState.clear();
   }

   Product::Product(const char * recSku, const char * recName, const char * recUnit, int recqty, bool recTax, double recProdPrice, int recQtyNeeded)
   {
      name(recName);
      type = 'N';
      strncpy(skuData, recSku, (max_sku_length + 1));
      strncpy(productDescriptiion, recUnit, (max_unit_length + 1));
      qtyInHand = recqty;
      qtyNeededData = recQtyNeeded;
      priceData = recProdPrice;
      tax = recTax;
   }

   Product::Product(const Product & src)
   {
      /*type = src.type;*/
      strcpy(skuData, src.skuData);
      strcpy(productDescriptiion, src.productDescriptiion);

      if (src.pProdName != nullptr)
      {
         pProdName = new char[strlen(src.pProdName) + 1];
         strcpy(pProdName, src.pProdName);
      }
      else
      {
         pProdName = nullptr;
      }
      qtyInHand = src.qtyInHand;
      qtyNeededData = src.qtyNeededData;
      priceData = src.priceData;
      tax = src.tax;
      if (!(src.ProdErrorState.isClear()))
      {
         ProdErrorState.message(src.ProdErrorState.message());
      }
   }

   Product Product::operator=(const Product & src)
   {
      if (strcmp(this->skuData, src.skuData) != 0)
      {
         /*type = src.type;*/
         strcpy(skuData, src.skuData);
         strcpy(productDescriptiion, src.productDescriptiion);

         delete[] pProdName;
         pProdName = new char[strlen(src.pProdName) + 1];
         strcpy(pProdName, src.pProdName);

         qtyInHand = src.qtyInHand;
         qtyNeededData = src.qtyNeededData;
         priceData = src.priceData;
         tax = src.tax;
         if (!(src.ProdErrorState.isClear()))
         {
            ProdErrorState.message(src.ProdErrorState.message());
         }
      }
      return (*this);
   }

   Product::~Product()
   {
      delete[] pProdName;
   }

   std::fstream & Product::store(std::fstream & file, bool newLine/* = true*/) const
   {
      file << type << "," << skuData << "," << pProdName << "," << productDescriptiion << "," << qtyInHand
         << "," << priceData << "," << tax << "," << qtyNeededData;
      if (!ProdErrorState.isClear())
      {
         file << ProdErrorState.message();
      }
      if (newLine)
      {
         file << std::endl;
      }
      return(file);
   }

   std::fstream & Product::load(std::fstream & file)
   {
      Product objHolder;
      std::string str;

      for (int i = 0; i < 7; i++)
      {

         std::getline(file, str, ',');
         std::stringstream inputHolder(str);
         switch (i)
         {
         case 0:
            inputHolder >> objHolder.skuData;
            break;
         case 1:
            objHolder.name(inputHolder.str().c_str());
            break;
         case 2:
            inputHolder >> objHolder.productDescriptiion;
            break;
         case 3:
            inputHolder >> objHolder.qtyInHand;
            break;
         case 4:
            inputHolder >> objHolder.priceData;
            break;
         case 5:
            inputHolder >> objHolder.tax;
            break;
         case 6:
            inputHolder >> objHolder.qtyNeededData;
            break;
         }
      }
      if (!file.fail())
      {
         ProdErrorState.clear();
         *this = objHolder;
      }
      return(file);
   }//   std::fstream & Product::load(std::fstream & file)

   std::ostream & Product::write(std::ostream & os, bool linear/*= true*/) const
   {
      
      if (ProdErrorState.isClear())
      {
         if (linear)
         {
            os << std::left << std::setw(max_sku_length) << sku() << '|' << std::setw(20) << name()
               << '|' << std::setw(7) << std::setprecision(2) << std::fixed;
            os << std::right;
            if (tax)
            {
               os << price() * (1 + TAX_RATE);
            }
            else
            {
               os << price();
            }
            os << "|" << std::setw(4) << quantity() << "|" << std::setw(10) << std::left
               << unit() << std::right << "|" << std::setw(4) << qtyNeeded() << "|";
         }
         else
         {
            os << " Sku: " << sku() << std::endl;
            os << " Name (no spaces): " << name() << std::endl;
            os << " Price : " << price() << std::endl << " Price after tax : ";
            if (tax)
            {
               os << (price() * (1 + TAX_RATE)) << std::endl;
            }
            else
            {
               os << "N/A" << std::endl;
            }
            os << " Quantity on hand : " << quantity() << ' ' << unit() << std::endl;
            os << " Quantity needed : " << qtyNeeded() << std::endl;
         }
      }
      else
      {
         os << ProdErrorState.message();
      }
      return (os);
   }

   std::istream & Product::read(std::istream & is)
   {
      Product prodHolder;
      char taxHolder;
      std::string str;
      ProdErrorState.clear();
      std::cout << " Sku: ";
      is >> prodHolder.skuData;
      std::cout << " Name (no spaces): ";
      is >> str;
      prodHolder.name(str.c_str());
      std::cout << " Unit: ";
      is >> prodHolder.productDescriptiion;
      std::cout << " Taxed? (y/n): ";
      is >> taxHolder;
      
      if (!(taxHolder == 'Y' || taxHolder == 'y' || taxHolder == 'N' || taxHolder == 'n'))
      {
         is.setstate(std::ios::failbit);
         setProError("Only (Y)es or (N)o are acceptable");
      }
      else
      {
         if (taxHolder == 'y' || taxHolder == 'Y')
         {
            prodHolder.tax = true;
         }
         else
         {
            prodHolder.tax = false;
         }
         std::cout << " Price: ";
         is >> prodHolder.priceData;
         if (is.fail())//double
         {
            is.setstate(std::ios::failbit);
            setProError("Invalid Price Entry");
         }
         else
         {
            std::cout << " Quantity on hand: ";
            is >> prodHolder.qtyInHand;
            if (is.fail())//int
            {
               is.setstate(std::ios::failbit);
               setProError("Invalid Quantity Entry");
            }
            else
            {
               std::cout << " Quantity needed: ";
               is >> prodHolder.qtyNeededData;
               if (is.fail())//int
               {
                  is.setstate(std::ios::failbit);
                  setProError("Invalid Quantity Needed Entry");
               }
               else
               {
                  *this = prodHolder;
               }
            }
         }
      }
      return (is);
   }//   std::istream & Product::read(std::istream & is)

   bool Product::operator==(const char *recSku) const
   {
      return (strcmp(recSku, this->skuData) == 0);
   }

   double Product::total_cost() const
   {
      return (tax ? (qtyInHand * priceData * (1 + TAX_RATE)) : (qtyInHand * priceData));
   }

   void Product::quantity(int recNumUnitInHands)
   {
      qtyInHand = recNumUnitInHands;
   }

   bool Product::isEmpty() const
   {
      return (pProdName == nullptr);
   }

   int Product::qtyNeeded() const
   {
      return (qtyNeededData);
   }

   int Product::quantity() const
   {
      return (qtyInHand);
   }

   bool Product::operator>(const char * recSku) const
   {
      return (strcmp(this->skuData, recSku) > 0);
   }

   bool Product::operator>(const iProduct & recProduct) const
   {
      return (strcmp(this->pProdName, recProduct.name()) > 0);
      //return (strcmp(this->pProdName, recProduct.pProdName) > 0);
   }

   int Product::operator+=(int addOrRemoveItem)
   {
      return (addOrRemoveItem > 0 ? (qtyInHand += addOrRemoveItem) : qtyInHand);
   }

   void Product::setProError(const char * str)
   {
      ProdErrorState.message(str);
   }

   const char* Product::sku() const
   {
      return (skuData);
   }

   char Product::name()
   {
      return (*pProdName);
   }

   std::ostream & operator<<(std::ostream & os, const iProduct & recProduct)
   {
      return (recProduct.write(os, true));
   }

   std::istream & operator>>(std::istream & is, iProduct & recProduct)
   {
      return (recProduct.read(is));
   }

   double operator+=(double & recDouble, const iProduct & recProduct)
   {
      return (recDouble += recProduct.total_cost());
   }

}