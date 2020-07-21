//
//  fact_value_test.cpp
//  Nadia-CPP
//
//  Created by Kwang Je Lee on 22/4/20.
//  Copyright © 2020 Dean Lee. All rights reserved.
//

#include "fact_value_test.hpp"
#include "fact_boolean_value.hpp"
#include "fact_string_value.hpp"
#include "fact_date_value.hpp"
#include "fact_defi_string_value.hpp"
#include "fact_double_value.hpp"
#include "fact_hash_value.hpp"
#include "fact_integer_value.hpp"
#include "fact_url_value.hpp"
#include "fact_uuid_value.hpp"
#include "fact_list_value.hpp"

shared_ptr<Fact_Boolean_Value<bool>> Fact_Value_Test::generateFactBooleanValue()
{
    shared_ptr<Fact_Boolean_Value<bool>> fbv = make_shared<Fact_Boolean_Value<bool>>(true);
    shared_ptr<Fact_Boolean_Value<bool>> negatedFbv = fbv->negatingValue();
    bool firstCondition = *fbv->getValue() == 1 && *fbv->getFactValueType() == Fact_Value_Type::BOOLEAN;
    bool secondCondition = negatedFbv.get() != nullptr && *negatedFbv->getValue() == 0;
    
    shared_ptr<Fact_Boolean_Value<bool>> secondFbv = make_shared<Fact_Boolean_Value<bool>>(fbv);
    bool thirdCondition = *secondFbv->getValue() == *fbv->getValue() && *secondFbv->getFactValueType() == *fbv->getFactValueType();
    
    if(firstCondition && secondCondition && thirdCondition)
    {
        cout << "Fact_Boolean_Value TEST Passed !!" << endl;
    }
    else
    {
        cout << "Fact_Boolean_Value TEST NOT Passed !!" << endl;
    }
    
    return fbv;
}

shared_ptr<Fact_String_Value<string>> Fact_Value_Test::generateFactStringValue()
{
    shared_ptr<Fact_String_Value<string>> fsv = make_shared<Fact_String_Value<string>>("work");
    
    bool firstCondition = fsv->getValue()->compare("work") == 0 && *fsv->getFactValueType() == Fact_Value_Type::STRING;
    
    shared_ptr<Fact_String_Value<string>> secondFsv = make_shared<Fact_String_Value<string>>(fsv);
    bool secondCondition = *secondFsv->getValue() == *fsv->getValue() && *secondFsv->getFactValueType() == *fsv->getFactValueType();
       
    if(firstCondition && secondCondition)
    {
        cout << "Fact_String_Value TEST Passed !!" << endl;
    }
    else
    {
        cout << "Fact_String_Value TEST NOT Passed !!" << endl;
    }
    
    return fsv;
}

shared_ptr<Fact_Date_Value<Date>> Fact_Value_Test::generateFactDateValue()
{
    shared_ptr<Fact_Date_Value<Date>> fdv = make_shared<Fact_Date_Value<Date>>(Date_Test::generateDate0());

    Date newDate("1/12/2019");
    
    bool firstCondition = fdv->getValue()->getWholeDateValueInString().compare(newDate.getWholeDateValueInString()) == 0 && *fdv->getFactValueType() == Fact_Value_Type::DATE;
       
    shared_ptr<Fact_Date_Value<Date>> secondFdv = make_shared<Fact_Date_Value<Date>>(fdv);
    bool secondCondition = secondFdv->getValue()->getWholeDateValueInString().compare(fdv->getValue()->getWholeDateValueInString()) == 0 && *secondFdv->getFactValueType() == *fdv->getFactValueType();
          
    if(firstCondition && secondCondition)
    {
        cout << "Fact_Date_Value TEST Passed !!" << endl;
    }
    else
    {
        cout << "Fact_Date_Value TEST NOT Passed !!" << endl;
    }
    return fdv;
}

shared_ptr<Fact_Defi_String_Value<string>> Fact_Value_Test::generateFactDefiStringValue()
{
    shared_ptr<Fact_Defi_String_Value<string>> fdsv = make_shared<Fact_Defi_String_Value<string>>("\"this is DEFI STRING\"");
        
    bool firstCondition = fdsv->getValue()->compare("this is DEFI STRING") == 0 && *fdsv->getFactValueType() == Fact_Value_Type::DEFI_STRING;
           
    shared_ptr<Fact_Defi_String_Value<string>> secondFdsv = make_shared<Fact_Defi_String_Value<string>>(fdsv);
    bool secondCondition = secondFdsv->getValue()->compare(*fdsv->getValue()) == 0 && *secondFdsv->getFactValueType() == *fdsv->getFactValueType();
    if(firstCondition && secondCondition)
    {
        cout << "Fact_Defi_String_Value TEST Passed !!" << endl;
    }
    else
    {
        cout << "Fact_Defi_String_Value TEST NOT Passed !!" << endl;
    }
    return fdsv;
}

shared_ptr<Fact_Double_Value<double>> Fact_Value_Test::generateFactDoubleValue()
{
    shared_ptr<Fact_Double_Value<double>> fdv = make_shared<Fact_Double_Value<double>>(5.435);
    
    bool firstCondition = *fdv->getValue() == 5.435 && *fdv->getFactValueType() == Fact_Value_Type::DECIMAL;
           
    shared_ptr<Fact_Double_Value<double>> secondFdv = make_shared<Fact_Double_Value<double>>(fdv);
    bool secondCondition = *secondFdv->getValue() == *fdv->getValue() && *secondFdv->getFactValueType() == *fdv->getFactValueType();
    
    if(firstCondition && secondCondition)
    {
        cout << "Fact_Double_Value TEST Passed !!" << endl;
    }
    else
    {
        cout << "Fact_Double_Value TEST NOT Passed !!" << endl;
    }
        return fdv;
}

shared_ptr<Fact_Hash_Value<string>> Fact_Value_Test::generateFactHashValue()
{
    shared_ptr<Fact_Hash_Value<string>> fhv = make_shared<Fact_Hash_Value<string>>("182cb50835d4704545ec9a2e4f09cab35342706f");

    bool firstCondition = fhv->getValue()->compare("182cb50835d4704545ec9a2e4f09cab35342706f") == 0 && *fhv->getFactValueType() == Fact_Value_Type::HASH;

    shared_ptr<Fact_Hash_Value<string>> secondFhv = make_shared<Fact_Hash_Value<string>>(fhv);
    bool secondCondition = secondFhv->getValue()->compare(*fhv->getValue()) == 0 && *secondFhv->getFactValueType() == *fhv->getFactValueType();
    
    if(firstCondition && secondCondition)
    {
        cout << "Fact_Hash_Value TEST Passed !!" << endl;
    }
    else
    {
        cout << "Fact_Hash_Value TEST NOT Passed !!" << endl;
    }
    return fhv;
}

shared_ptr<Fact_Integer_Value<int>> Fact_Value_Test::generateFactIntegerValue()
{
    shared_ptr<Fact_Integer_Value<int>> fiv = make_shared<Fact_Integer_Value<int>>(123);
    
    bool firstCondition = *fiv->getValue() == 123 && *fiv->getFactValueType() == Fact_Value_Type::INTEGER;
              
    shared_ptr<Fact_Integer_Value<int>> secondFiv = make_shared<Fact_Integer_Value<int>>(fiv);
    bool secondCondition = *secondFiv->getValue() == *fiv->getValue() && *secondFiv->getFactValueType() == *fiv->getFactValueType();
       
    if(firstCondition && secondCondition)
    {
        cout << "Fact_Integer_Value TEST Passed !!" << endl;
    }
    else
    {
        cout << "Fact_Integer_Value TEST NOT Passed !!" << endl;
    }
    return fiv;
}

shared_ptr<Fact_URL_Value<string>> Fact_Value_Test::generateFactURLValue()
{
    shared_ptr<Fact_URL_Value<string>> fuv = make_shared<Fact_URL_Value<string>>("www.test.com");
    
    bool firstCondition = fuv->getValue()->compare("www.test.com") == 0 && *fuv->getFactValueType() == Fact_Value_Type::URL;
              
    shared_ptr<Fact_URL_Value<string>> secondFuv = make_shared<Fact_URL_Value<string>>(fuv);
    bool secondCondition = secondFuv->getValue()->compare(*fuv->getValue()) == 0 && *secondFuv->getFactValueType() == *fuv->getFactValueType();

    if(firstCondition && secondCondition)
    {
        cout << "Fact_URL_Value TEST Passed !!" << endl;
    }
    else
    {
        cout << "Fact_URL_Value TEST NOT Passed !!" << endl;
    }
    
    return fuv;
}

shared_ptr<Fact_UUID_Value<string>> Fact_Value_Test::generateFactUUIDValue()
{
    shared_ptr<Fact_UUID_Value<string>> fuuv = make_shared<Fact_UUID_Value<string>>("ffa4788a-a33f-11e7-abc4-cec278b6b50a");
    
    bool firstCondition = fuuv->getValue()->compare("ffa4788a-a33f-11e7-abc4-cec278b6b50a") == 0 && *fuuv->getFactValueType() == Fact_Value_Type::UUID;
              
    shared_ptr<Fact_UUID_Value<string>> secondFuuv = make_shared<Fact_UUID_Value<string>>(fuuv);
    bool secondCondition = secondFuuv->getValue()->compare(*fuuv->getValue()) == 0 && *secondFuuv->getFactValueType() == *fuuv->getFactValueType();
    
    if(firstCondition && secondCondition)
    {
        cout << "Fact_UUID_Value TEST Passed !!" << endl;
    }
    else
    {
        cout << "Fact_UUID_Value TEST NOT Passed !!" << endl;
    }
    return fuuv;
}


shared_ptr<Fact_List_Value<vector<any>>> Fact_Value_Test::generateFactListValue()
{
    any varFuv(generateFactURLValue());

    any varFidv(generateFactUUIDValue());
    
    any varFbv(generateFactBooleanValue());

    any varFsv(generateFactStringValue());

    any varFdv(generateFactDateValue());

    shared_ptr<Fact_Defi_String_Value<string>> fdsv = generateFactDefiStringValue();
    any varFdsv(fdsv);
    shared_ptr<Fact_Defi_String_Value<string>> fdsv2 = any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(varFdsv);
    cout << "value: " <<*(fdsv2.get()->getValue().get()) << endl;
    any varFdov(generateFactDoubleValue());

    any varFhv(generateFactHashValue());

    any varFiv(generateFactIntegerValue());
    
    vector<any> vec = {varFdov, varFiv, varFhv, varFuv, varFidv, varFbv, varFsv, varFdv, varFdsv};
    shared_ptr<Fact_List_Value<vector<any>>> flv = make_shared<Fact_List_Value<vector<any>>>(vec);
    
    return flv;
    
}

void Fact_Value_Test::printFactListValue()
{
    Fact_List_Value<vector<any>> flv = *generateFactListValue();
    
    vector<any> vectorValue = *flv.getValue();
    optional<Fact_Boolean_Value<bool>> fbv;
    optional<Fact_String_Value<string>> fsv;
    optional<Fact_Date_Value<Date>> fdv;
    optional<Fact_Defi_String_Value<string>> fdsv;
    optional<Fact_Double_Value<double>> fdov;
    optional<Fact_Hash_Value<string>> fhv;
    optional<Fact_Integer_Value<int>> fiv;
    optional<Fact_URL_Value<string>> fuv;
    optional<Fact_UUID_Value<string>> fidv;

    for(any item : vectorValue)
    {
        switch(typeIndexMap[item.type()])
        {
            case 0:
            {
                fbv = *(any_cast<shared_ptr<Fact_Boolean_Value<bool>>>(item).get());
                cout << "Fact_Boolean_Value<bool> value: " << *fbv->getValue() << ", Fact Value Type: "<< *fbv->getFactValueType() << endl;
                break;
                
            }
            case 1:
            {
                fsv = *(any_cast<shared_ptr<Fact_String_Value<string>>>(item).get());
                cout << "Fact_String_Value<string> value: " << *fsv->getValue() << ", Fact Value Type: " << *fsv->getFactValueType()<< endl;
                break;
            }
            case 2:
            {
                fdv = *(any_cast<shared_ptr<Fact_Date_Value<Date>>>(item).get());
                cout << "Fact_Date_Value<Date> value: " << fdv->getValue()->getWholeDateValueInString() << ", Fact Value Type: " << *fdv->getFactValueType()<< endl;
                break;
            }
            case 3:
            {
                shared_ptr<Fact_Defi_String_Value<string>> fdsv2 = any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(item);
                cout << "Fact_Defi_String_Value<string> value: " << *(fdsv2->getValue()) << ", Fact Value Type: " << *fdsv2->getFactValueType()<< endl;
                
                
                fdsv = *(any_cast<shared_ptr<Fact_Defi_String_Value<string>>>(item).get());
                cout << "Fact_Defi_String_Value<string> value: " << *(fdsv->getValue()) << ", Fact Value Type: " << *fdsv->getFactValueType()<< endl;
                break;
            }
            case 4:
            {
                fdov = *(any_cast<shared_ptr<Fact_Double_Value<double>>>(item));
                cout << "Fact_Double_Value<double> value: " << *fdov->getValue() << ", Fact Value Type: " << *fdov->getFactValueType()<< endl;
                break;
            }
            case 5:
            {
                fhv = *(any_cast<shared_ptr<Fact_Hash_Value<string>>>(item).get());
                cout << "Fact_Hash_Value<string> value: " << *fhv->getValue() << ", Fact Value Type: " << *fhv->getFactValueType()<< endl;
                break;
            }
            case 6:
            {
                fiv = *(any_cast<shared_ptr<Fact_Integer_Value<int>>>(item).get());
                cout << "Fact_Integer_Value<int> value: " << *fiv->getValue() << ", Fact Value Type: " << *fiv->getFactValueType()<< endl;
                break;
            }
            case 7:
            {
                fuv = *(any_cast<shared_ptr<Fact_URL_Value<string>>>(item).get());
                cout << "Fact_URL_Value<string> value: " << *fuv->getValue() << ", Fact Value Type: " << *fuv->getFactValueType()<< endl;
                break;
            }
            case 8:
            {
                fidv = *(any_cast<shared_ptr<Fact_UUID_Value<string>>>(item).get());
                cout << "Fact_UUID_Value<string> value: " << *fidv->getValue() << ", Fact Value Type: " << *fidv->getFactValueType()<< endl;
                break;
            }
        }
    }
}

void Fact_Value_Test::testGenerateFactValue()
{
//    generateFactBooleanValue();
//    generateFactStringValue();
//    generateFactDateValue();
//    generateFactDefiStringValue();
//    generateFactDoubleValue();
//    generateFactHashValue();
//    generateFactIntegerValue();
//    generateFactURLValue();
//    generateFactUUIDValue();
    printFactListValue();
}
