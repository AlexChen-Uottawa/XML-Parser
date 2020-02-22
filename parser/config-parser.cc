// parser/config-parser.cc



#include "parser/config-parser.h"

void MerchantInfo::Print() const {
  std::cout << "Merchant Info" << std::endl;
  std::cout << "\tMerchant Name: " << merchant_name_ << std::endl;
  std::cout << "\tMerchant Street: " << merchant_street_ << std::endl;
  std::cout << "\tMerchant City Post Code: " << merchant_city_post_code_
    << std::endl;
  std::cout << "\tMerchant State: " << merchant_state_ << std::endl;
  std::cout << "\tMerchant Country Code: " << merchant_country_code_
    << std::endl;
  std::cout << "\tMerchant Phone: " << merchant_phone_ << std::endl;
  std::cout << "\tMerchant Id: " << merchant_id_ << std::endl;
}

void PinPad::Print() const {
  std::cout << "PinPad info" << std::endl;
  std::cout << "\tName: " << name_ << std::endl;
  std::cout << "\tConnection Type: " << connection_type_ << std::endl;
  std::cout << "\tConnection Port: " << connection_port_ << std::endl;
  std::cout << "\tConnection Model: " << connection_mode_ << std::endl;
  std::cout << "\tEncryption Method: " << encryption_method_ << std::endl;
  if (swipe_card_number_check_)
    std::cout << "\tSwipe Card Number Check" << std::endl;
  if (msr_) std::cout << "\tMSR" << std::endl;
  if (emv_) std::cout << "\tEMV" << std::endl;
  if (prompt_credit_debit_) std::cout << "\tPrompt Credit Debit" << std::endl;
  if (confirm_amount_) std::cout << "\tConfirm Amount" << std::endl;
}


void ConfigParser::Parse(const std::string &filename) {
  using boost::property_tree::ptree;
  // Create empty property tree object
  ptree tree;

  // Parse the XML into the property tree
  read_xml(filename, tree);

  BOOST_FOREACH(ptree::value_type const &v, tree.get_child("FuelLynxConfig")) {
    if (v.first == "MerchantInfo") {
      // Read in each entry of merchant info.
      std::string
        merchant_name = v.second.get<std::string>("MerchantName"),
        merchant_street = v.second.get<std::string>("MerchantStreet"),
        merchant_city_post_code =
          v.second.get<std::string>("MerchantCityPostCode"),
        merchant_state = v.second.get<std::string>("MerchantState"),
        merchant_country_code =
          v.second.get<std::string>("MerchantCountryCode"),
        merchant_phone = v.second.get<std::string>("MerchantPhone"),
        merchant_fax = v.second.get<std::string>("MerchantFax"),
        merchant_id = v.second.get<std::string>("MerchantId");

      // Create MerchantInfo
      merchant_info_ = new MerchantInfo(merchant_name, merchant_street,
          merchant_city_post_code, merchant_state, merchant_country_code,
          merchant_phone, merchant_fax, merchant_id);
    } else if (v.first == "PinPads") {
      // The PinPad container may be repeated. Iterate each entry.
      // This time use for loop to deal with it
      ptree pin_pads_tree = tree.get_child("FuelLynxConfig.PinPads");
      for (ptree::const_iterator it = pin_pads_tree.begin();
           it != pin_pads_tree.end(); it++) {
        if (it->first == "PinPad") {
          // Get the essential info
          std::string name = it->second.get<std::string>("<xmlattr>.name"),
            connection_type = it->second.get<std::string>("ConnectionType"),
            connection_port = it->second.get<std::string>("ConnectionPort"),
            connection_mode = it->second.get<std::string>("ConnectionMode"),
            encryption_method = it->second.get<std::string>("EncryptionMethod");

          // Get flag elements may be present or not.
          bool swipe_card_number_check, msr, emv, prompt_credit_debit,
               confirm_amount;
          swipe_card_number_check = msr = emv = prompt_credit_debit =
            confirm_amount = false;

          ptree::const_assoc_iterator check =
            it->second.find("SwipeCardNumberCheck");
          if (check != it->second.not_found()) swipe_card_number_check = true;

          check = it->second.find("MSR");
          if (check != it->second.not_found()) msr = true;

          check = it->second.find("EMV");
          if (check != it->second.not_found()) emv = true;

          check = it->second.find("PromptCreditDebit");
          if (check != it->second.not_found()) prompt_credit_debit = true;

          check = it->second.find("ConfirmAmount");
          if (check != it->second.not_found()) confirm_amount = true;


          PinPad* pin_pad = new PinPad(name, connection_type, connection_port,
              connection_mode, encryption_method, swipe_card_number_check,
              msr, emv, prompt_credit_debit, confirm_amount);

          // Add to vector
          pin_pads_.push_back(pin_pad);
        } else {
          std::cout << "Warning: encounter an un-expected tag in <PinPads>: "
                    << it->first << ". Just skip it." << std::endl;
        }
      }
    } else {
      std::cout << "Warning: encounter an un-expected tag: "
                << v.first << ". Just skip it." << std::endl;
    }
  }
}


void ConfigParser::Print() const {
  // Print the error info to std::cout rather than std::cerr so that we can
  // dump the useful information as much as possible.
  if (merchant_info_ == NULL) {
    std::cout << "Error! No merchant info is available.";
  } else {
    merchant_info_->Print();
  }
  if (pin_pads_.size() == 0) {
    std::cout << "Error! No pin pad info is available.";
  } else {
    for (std::vector<PinPad* >::const_iterator it = pin_pads_.begin();
         it != pin_pads_.end(); it++) {
      (*it)->Print();
    }
  }
}


ConfigParser::~ConfigParser() {
  if (merchant_info_ != NULL) delete merchant_info_;
  for (size_t i = 0; i < pin_pads_.size(); i++) {
    delete pin_pads_[i];
  }
}

