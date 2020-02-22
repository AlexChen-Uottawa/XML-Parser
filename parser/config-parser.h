// parser/config-parser.h

// Copyright 2019 Leo Chen

#ifndef XMLPARSER_PARSER_CONFIG_PARSER_H_
#define XMLPARSER_PARSER_CONFIG_PARSER_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <iostream>

class MerchantInfo {
 public:
  MerchantInfo(std::string merchant_name, std::string merchant_street,
      std::string merchant_city_post_code, std::string merchant_state,
      std::string merchant_country_code, std::string merchant_phone,
      std::string merchant_fax, std::string merchant_id) :
    merchant_name_(merchant_name), merchant_street_(merchant_street),
    merchant_city_post_code_(merchant_city_post_code),
    merchant_state_(merchant_state),
    merchant_country_code_(merchant_country_code),
    merchant_phone_(merchant_phone), merchant_fax_(merchant_fax),
    merchant_id_(merchant_id) { }
  
  // Dump the merchant info in human readable format.
  void Print() const;

  // Just an example for set/get function. Actually we can do it for each
  // private variable.
  inline void SetMerchantName(const std::string &merchant_name) {
    merchant_name_ = merchant_name;
  }
  inline std::string GetMerchantName() const {
    return merchant_name_;
  }
 private:
  std::string merchant_name_;
  std::string merchant_street_;
  std::string merchant_city_post_code_;
  std::string merchant_state_;
  std::string merchant_country_code_;
  std::string merchant_phone_;
  std::string merchant_fax_;
  std::string merchant_id_;
};

class PinPad {
 public:
  PinPad(std::string name, std::string connection_type,
      std::string connection_port, std::string connection_mode,
      std::string encryption_method, bool swipe_card_number_check,
      bool msr, bool emv, bool prompt_credit_debit, bool confirm_amount) :
    name_(name), connection_type_(connection_type),
    connection_port_(connection_port), connection_mode_(connection_mode),
    encryption_method_(encryption_method),
    swipe_card_number_check_(swipe_card_number_check), msr_(msr), emv_(emv),
    prompt_credit_debit_(prompt_credit_debit),
    confirm_amount_(confirm_amount) { }

  // Dump the pin pad info in human readable format.
  void Print() const;

  // Just an example for set/get function. Actually we can do it for each
  // private variable.
  inline void SetConnectionType(const std::string &connection_type) {
    connection_type_ = connection_type;
  }
  inline std::string GetConnectionType() const {
    return connection_type_;
  }
 private:
  std::string name_;
  std::string connection_type_;
  std::string connection_port_;
  std::string connection_mode_;
  std::string encryption_method_;
  bool swipe_card_number_check_;
  bool msr_;
  bool emv_;
  bool prompt_credit_debit_;
  bool confirm_amount_;
};

class ConfigParser {
 public:
  // Read the test XML configuration data from file using the boost property
  // tree data structure. Parse the content to get the information of merchant
  // and pin pads.
  void Parse(const std::string &filename);

  // Dump the configuration in human readable format.
  void Print() const;

  // Release the memory.
  ~ConfigParser();
 private:
  MerchantInfo* merchant_info_;
  // Store the pointer rather than object to avoid the consume of data copying
  // as the size of vector.
  // increases.
  std::vector<PinPad* > pin_pads_;
};

#endif
