// Note: The license below is based on the template at:
// http://opensource.org/licenses/BSD-3-Clause

// Copyright (C) 2020 Regents of the University of Texas
//All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:

// o Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.

// o Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.

// o Neither the name of the copyright holders nor the names of its
//   contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Original Author(s):
// Mertcan Temel         <mert@utexas.edu>

#include <iostream>
#include <queue>          // std::queue
#include <fstream>

#include <string>
#include <sstream>
#include <cstring>

#include <cmath>

using namespace std;

#include "adders.h"

#include "pp_gen.h"

#include "wallace.h"

#include "dadda.h"

void enter_license (queue<string>& verilog) {

  verilog.push("// Note: The license below is based on the template at:");
  verilog.push("// http://opensource.org/licenses/BSD-3-Clause");

  verilog.push("// Copyright (C) 2020 Regents of the University of Texas");
  verilog.push("//All rights reserved.");
  verilog.push("");
  verilog.push("// Redistribution and use in source and binary forms, with or without");
  verilog.push("// modification, are permitted provided that the following conditions are");
  verilog.push("// met:");
  verilog.push("");
  verilog.push("// o Redistributions of source code must retain the above copyright");
  verilog.push("//   notice, this list of conditions and the following disclaimer.");
  verilog.push("");
  verilog.push("// o Redistributions in binary form must reproduce the above copyright");
  verilog.push("//   notice, this list of conditions and the following disclaimer in the");
  verilog.push("//   documentation and/or other materials provided with the distribution.");
  verilog.push("");
  verilog.push("// o Neither the name of the copyright holders nor the names of its");
  verilog.push("//   contributors may be used to endorse or promote products derived");
  verilog.push("//   from this software without specific prior written permission.");
  verilog.push("");
  verilog.push("// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS");
  verilog.push("// \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT");
  verilog.push("// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR");
  verilog.push("// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT");
  verilog.push("// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,");
  verilog.push("// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT");
  verilog.push("// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,");
  verilog.push("// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY");
  verilog.push("// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT");
  verilog.push("// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE");
  verilog.push("// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.");
  verilog.push("");
  verilog.push("// Original Author(s):");
  verilog.push("// Mertcan Temel         <mert@utexas.edu>\n");

  verilog.push("// DO NOT REMOVE: This file is generator by Temel's multiplier generator. Download from https://github.com/temelmertcan/multgen.");

  verilog.push("");
}

void print_strings (string* s, int size){
  for (int i = 0; i<size; i++)
    cout << s[i] << endl;
}

string convertToString(char* a, int size)
{
  int i;
  string s = "";
  for (i = 0; i < size; i++) {
    s = s + a[i];
  }
  return s;
}

int interact_with_user (int argc, char **argv,
                        int& in1_size,
                        int& in2_size,
                        int& in3_size,
                        int& dot_size,
                        int& out_size,
                        bool& signed_mult,
                        bool& ha_fa_with_gates,
                        string& final_stage_adder,
                        string& pp_encoding,
                        string& tree,
                        string& main_type){




  if (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0) {
    cout << "\nUsers  may  pass  arguments  to  the  program  to  configure  the\n" <<
      "design.  Any configuration  not  selected in  the arguments  will\n" <<
      "start an interactive session to help the user select from allowed\n" <<
      "options. Allowed arguments are:\n\n" <<
      "  -def           : Generates a multiplier with hard-coded default configurations. Parts of these configs can be overriden by other arguments.\n" <<
      "  -type <arg>    : Functionality type of the design to be generated. <arg> can be (case sensitive): \n" <<
      "  \t StandAlone - just an isolated, stand-alone multiplier.\n " <<
      "  \t MAC        - multiply-and-accumulate.\n " <<
      "  \t FourMult   - create a stand-alone multiplier using 4 smaller isolated multipliers.\n " <<
      "  \t DOT        - a dot product module.\n" <<
      "  \t Adder      - create only an adder module, no multipliers.\n" <<
      "  -tree <arg>    : Summation tree to be used. <arg> can be: \n" <<
      "  \t DT         - Dadda tree.\n " <<
      "  \t WT         - Wallace tree.\n" <<
      "  -pp   <arg>    : PP encoding to be used. <arg> can be: \n" <<
      "  \t SSP        - signed, simple partial products.\n " <<
      "  \t USP        - unsigned, simple partial products.\n " <<
      "  \t SB2        - signed, booth encoding radix-2.\n " <<
      "  \t UB2        - unsigned, booth encoding radix-2.\n " <<
      "  \t SB4        - signed, booth encoding radix-4.\n " <<
      "  \t UB4        - unsigned, booth encoding radix-4.\n " <<
      "  \t SB8        - signed, booth encoding radix-8.\n " <<
      "  \t UB8        - unsigned, booth encoding radix-8.\n " <<
      "  \t SB16       - signed, booth encoding radix-16.\n " <<
      "  \t UB16       - unsigned, booth encoding radix-16.\n" <<
      "  -adder <arg>   : Vector adder to be used for final stage addition. <arg> can be: \n" <<
      "  \t RP         - Ripple-carry adder.\n " <<
      "  \t KS         - Kogge-Stone adder.\n " <<
      "  \t LF         - Ladner-Fischer adder.\n " <<
      "  \t HC         - Han-Carlson adder.\n" <<
      "  -in1size <arg> : Size of the first operand. <arg> should be a positive integer: \n" <<
      "  -in2size <arg> : Size of the second operand. <arg> should be a positive integer: \n" <<
      "  -in3size <arg> : Size of the third operand, when relevant. <arg> should be a positive integer: \n" <<
      "  -outsize <arg> : Size of the output. Useful when user wants to truncate the result. <arg> should be a positive integer: \n" <<
      "  -dotsize <arg> : Determines how many vector pairs should be in the dot product design. <arg> should be a positive integer greater than 1: \n" <<
      endl;

    return 2;
  }


  
  // defaults:
  ha_fa_with_gates = true;

  in1_size = -1;
  in2_size = -1;
  in3_size = -1;
  dot_size = -1;
  out_size = -1;
  bool auto_out_size = false;

  main_type = "";
  final_stage_adder = "";
  pp_encoding = "";
  tree = "";

  bool do_not_select_tree = false;
  bool do_not_ask_for_pp = false;

  if (strcmp(argv[1], "-def") == 0) {
    in1_size = 16;
    in2_size = 16;
    in3_size = 32;
    dot_size = 8;
    out_size = 50;

    main_type = "StandAlone";
    final_stage_adder = "RP";
    pp_encoding = "SB16";
    tree = "DT";
    ha_fa_with_gates = false;
    signed_mult = (pp_encoding[0] == 'S');
   

  }

  for (int i = 1; i+1 < argc; i+=2){
    if (strcmp(argv[i], "-type") == 0)
      main_type = argv[i+1];
    else if (strcmp(argv[i], "-tree") == 0)
      tree = argv[i+1];
    else if (strcmp(argv[i], "-pp") == 0){
       pp_encoding = argv[i+1];
      if (pp_encoding[0] == 'S'){
	signed_mult = true;
    
      } else if (pp_encoding[0] == 'U'){
	signed_mult = false;
      
      } else {
        cout << "Invalid pp encoding is passed. It should start with S or U, indicating signed/unsigned." << endl;
      }
    }else if (strcmp(argv[i], "-adder") == 0)
      final_stage_adder = argv[i+1];
    else if (strcmp(argv[i], "-in1size") == 0){
      sscanf(argv[i+1], "%d", &in1_size);
      auto_out_size = true;
    }else if (strcmp(argv[i], "-in2size") == 0){
      sscanf(argv[i+1], "%d", &in2_size);
      auto_out_size = true;
    }else if (strcmp(argv[i], "-in3size") == 0)
      sscanf(argv[i+1], "%d", &in3_size);
    else if (strcmp(argv[i], "-dotsize") == 0)
      sscanf(argv[i+1], "%d", &dot_size);
    else if (strcmp(argv[i], "-outsize") == 0)
      sscanf(argv[i+1], "%d", &out_size);
    else if (strcmp(argv[i], "-def") == 0)
      i--;
    else {
      cout << "Unrecognized argument: " << argv[i] << endl;
    }

  }

  string s = "";
  if (main_type != "StandAlone" &&
      main_type != "MAC" &&
      main_type != "FourMult" &&
      main_type != "DOT" &&
      main_type != "Adder")
    while(1) {

      if (main_type != "")
        cout << "Invalid type is passed. Please select from the list below" << endl;

      cout << "1. Stand-alone (Isolated) Multiplier  " << endl;
      cout << "2. MAC (a * b + c) " << endl;
      cout << "3. Merged Four Multipliers " << endl;
      cout << "4. Dot Product " << endl;
      cout << "5. Only a Vector Adder " << endl;
      //cout << "2.  " << endl;

      cout << "Select Multiplier Type: ";
      cin >> s;

      if (s.compare ("1") == 0) {
        main_type = "StandAlone";
        break;
      } else if (s.compare ("2") == 0)  {
        main_type = "MAC";
        break;
      } else if (s.compare ("3") == 0)  {
        main_type = "FourMult";
        break;
      } else if (s.compare ("4") == 0)  {
        main_type = "DOT";
        break;
      } else if (s.compare ("5") == 0)  {
        main_type = "Adder";
	break;
      } else
        cout << "Invalid Selection!" << endl;
    }

  if (main_type == "Adder"){
     do_not_select_tree = true;
     do_not_ask_for_pp = true;
  }
    

  if (tree != "DT" &&
      tree != "WT")
    while (!do_not_select_tree) {

      if (tree != "")
        cout << "Invalid tree is passed. Please select from the list below" << endl;

      cout << "1. Wallace Tree " << endl;
      cout << "2. Dadda Tree " << endl;

      cout << "Select Summation Tree Algorithm: ";
      cin >> s;
      if (s.compare ("1") == 0) {
        tree = "WT";
        break;
      }else if (s.compare ("2") == 0)  {
        tree = "DT";
        break;
      } else
        cout << "Invalid Selection!" << endl;

    }

  if (pp_encoding != "SSP" &&
      pp_encoding != "USP" &&
      pp_encoding != "SB2" &&
      pp_encoding != "UB2" &&
      pp_encoding != "SB4" &&
      pp_encoding != "UB4" &&
      pp_encoding != "SB8" &&
      pp_encoding != "UB8" &&
      pp_encoding != "SB16" &&
      pp_encoding != "UB16")
    while (!do_not_ask_for_pp) {

      if (pp_encoding != "")
        cout << "Invalid pp_encoding (" << pp_encoding << " is passed. Please select from the list below" << endl;

      cout << "1. Signed " << endl;
      cout << "2. Unsigned" << endl;

      cout << "Signed or Unsigned Multiplication?: ";
      cin >> s;
      if (s.compare ("1") == 0) {
        signed_mult = true;
      }else  if (s.compare ("2") == 0) {
        signed_mult = false;
      }else {
        cout << "Invalid Selection. Try again!" << endl;
        continue;
      }

      cout << "1. Simple" << endl;
      cout << "2. Booth radix-2" << endl;
      cout << "3. Booth radix-4" << endl;
      cout << "4. Booth radix-8" << endl;
      cout << "5. Booth radix-16" << endl;

      cout << "Select Partial Product Generation Algorithm: ";
      cin >> s;
      if (s.compare ("1") == 0) {
        pp_encoding = signed_mult ? "SSP" : "USP";
        break;
      }else  if (s.compare ("2") == 0) {
        pp_encoding = signed_mult ? "SB2" : "UB2";
        break;
      }else if (s.compare ("3") == 0)  {
        pp_encoding = signed_mult ? "SB4" : "UB4";
        break;
      }else if (s.compare ("4") == 0)  {
        pp_encoding = signed_mult ? "SB8" : "UB8";
        break;
      }else if (s.compare ("5") == 0)  {
        pp_encoding = signed_mult ? "SB16" : "UB16";
        break;
      }else
        cout << "Invalid Selection! Try again!" << endl;
    }

  if (final_stage_adder != "RP" &&
      final_stage_adder != "HC" &&
      final_stage_adder != "LF" &&
      final_stage_adder != "KS")
    while(1) {

      cout << "1. Ripple Carry Adder " << endl;
      cout << "2. Han-Carlson Adder " << endl;
      cout << "3. Ladner-Fischer Adder " << endl;
      cout << "4. Kogge-Stone Adder " << endl;

      cout << "Select Final Stage Adder Algorithm: ";
      cin >> s;
      if (s.compare ("1") == 0) {
        final_stage_adder = "RP";
        break;
      }else if (s.compare ("2") == 0)  {
        final_stage_adder = "HC";
        break;
      }else if (s.compare ("3") == 0)  {
        final_stage_adder = "LF";
        break;
      } else if (s.compare ("4") == 0)  {
        final_stage_adder = "KS";
        break;
      }
      else
        cout << "Invalid Selection!" << endl;

    }

  if (main_type.compare("Adder")==0) {
    if (in1_size < 0){
      cout << "Enter input size: ";
      cin >> in1_size;
    }
    return 0;
  }

  if (main_type.compare("StandAlone") == 0){
    if (in1_size < 0){
      cout << "Enter IN1 (Multiplier) size: ";
      cin >> in1_size;
    }
    if (in2_size < 0){
      cout << "Enter IN2 (Multiplicand) size: ";
      cin >> in2_size;
    }

    if (out_size < 0 && !auto_out_size ){
      cout << "Enter Output size (any value less than \""<< in1_size+in2_size << "\" will truncate the result): ";
      string in = "";
      cin >> in;
      if (std::stringstream(in) >> out_size) {
      }
      else out_size = in1_size+in2_size;
    } else if (out_size < 0)
      out_size = in1_size+in2_size;

  }

  if (main_type.compare("MAC") == 0){
    if (in1_size < 0){
      cout << "Enter IN1 (Multiplier) size: ";
      cin >> in1_size;
    }

    if (in2_size < 0){
      cout << "Enter IN2 (Multiplicand) size: ";
      cin >> in2_size;
    }

    if (in3_size < 0){
      cout << "Enter IN3 (Addend) size: ";
      cin >> in3_size;
    }

    int max_out_size = max(in1_size+in2_size+1,in3_size+1);
    if (out_size < 0 && !auto_out_size ){
      cout << "Enter Output size (any value less than \""
           << max_out_size
           << "\" will truncate the result): ";
      string in = "";
      cin >> in;
      if (std::stringstream(in) >> out_size) {
      }
      else out_size = max_out_size;

      if (out_size > max_out_size)
        out_size = max_out_size;
    } else if (out_size < 0)
      out_size = max_out_size;
  }

  if (main_type.compare("FourMult") == 0){
    bool in1_was_given = in1_size >= 0;
    while(1){
      if (in1_size < 0 || ((in1_size & 1) != 0)){
        cout << "Enter input vector (IN1 multiplier and IN2 multiplicand) size (should be divisible by 2): ";
        cin >> in1_size;
        in2_size = in1_size;
        //out_size = in1_size + in2_size;
        if ((in1_size & 1) == 0)
          break;
        cout << "Input size must be divisible by 2. ";
      }
    }

    if (!in1_was_given && (in3_size <= 0)){
      cout << "Enter IN3 size (Addend, i.e., the number to be added after multiplication) size (enter 0 to omit): ";
      cin >> in3_size;
    } else if (in3_size <= 0)
      in3_size = 0;

    int max_out_size = max(in1_size+in2_size+(in3_size>0?1:0),in3_size+1);
    if (out_size < 0 && !auto_out_size ){
      cout << "Enter Output size (any value less than \""
           << max_out_size
           << "\" will truncate the result): ";
      string in = "";
      cin >> in;
      if (std::stringstream(in) >> out_size) {
      }
      else out_size = max_out_size;

      if (out_size > max_out_size){
        out_size = max_out_size;
        cout << "Outsize is corrected to " << out_size << endl;
      }
    } else if (out_size < 0)
      out_size = max_out_size;
  }

  if (main_type.compare("DOT") == 0){
    bool in1_2_was_given = in1_size >= 0 || in2_size >= 0;
    if (in1_size < 0){
      cout << "Enter IN1 (Multiplier) size: ";
      cin >> in1_size;
    }

    if (in2_size < 0){
      cout << "Enter IN2 (Multiplicand) size: ";
      cin >> in2_size;
    }

    while (dot_size < 2){
      cout << "Enter dot product size (greater than 1): ";
      cin >> dot_size;
      if(dot_size<2)
        cout << "Dot product size should be a positive number >1." << endl;
    }

    if (!in1_2_was_given && (in3_size <= 0)){
      cout << "Enter IN3 (Addend, number to be added after multiplication) size (enter 0 to omit): ";
      cin >> in3_size;
    } else if (in3_size <= 0)
      in3_size = 0;

    int max_out_size = max(in1_size+in2_size+int((dot_size+1)/2)+(in3_size>0&&(dot_size&1)==0?1:0),in3_size+1);
    if (out_size < 0 && !auto_out_size ){
      cout << "Enter Output size (any value less than \""
           << max_out_size
           << "\" will truncate the result): ";
      string in = "";
      cin >> in;
      if (std::stringstream(in) >> out_size) {
      }
      else out_size = max_out_size;

      if (out_size > max_out_size)
        out_size = max_out_size;
    } else if (out_size < 0)
      out_size = max_out_size;
  }

  return 0;

}

int create_mult ( int  in1_size,
                  int  in2_size,
                  int  out_size,
                  string final_stage_adder,
                  string pp_encoding,
                  string tree,
                  bool create_fin_adder,
                  string& module_name,
                  std::list<int>& extra_ones_indices,
                  queue<string>& verilog,
                  int& adder_size,
                  bool**& zeros_in_output){

  int pp_dim1, pp_dim2;
  string** pp_matrix;

  module_name = tree + "_" + pp_encoding + "_"
    + (create_fin_adder?final_stage_adder + "_" : "")
    + to_string(in1_size) + "x"
    + to_string(in2_size)
    + (out_size != (in2_size+in1_size) ? "_" + to_string(out_size) : "" );

  if (create_fin_adder){

    verilog.push ("// Specification module to help understand what the design implements.");
    verilog.push ("module "+module_name+"_spec (");
    verilog.push("indent");
    verilog.push("indent");
    verilog.push ("input logic [" + to_string(in1_size-1) + ":0] IN1,");
    verilog.push ("input logic [" + to_string(in2_size-1) +  ":0] IN2,");
    verilog.push ("output logic design_is_correct, // is set to 1 iff the output of " + module_name + " matches its spec.");
    verilog.push ("output logic ["  + to_string(out_size-1) +  ":0] design_res,");
    verilog.push ("output logic ["  + to_string(out_size-1) +  ":0] spec_res);");
    verilog.push("outdent");
    verilog.push("");
    if (pp_encoding[0] == 'S')
      verilog.push("assign spec_res = signed'(IN1) * signed'(IN2);");
    else
      verilog.push("assign spec_res = IN1 * IN2;");

    verilog.push(module_name + " mult(IN1, IN2, design_res);");
    verilog.push("assign design_is_correct = ((spec_res == design_res) ? 1 : 0);");
    verilog.push("");
    verilog.push("outdent");
    verilog.push ("endmodule");
    verilog.push("");

    verilog.push ("\n");
  }

  verilog.push ("module " + module_name + "(");
  verilog.push("indent");
  verilog.push("indent");
  verilog.push ("input logic [" + to_string(in1_size - 1) + ":0] IN1," );
  verilog.push ("input logic [" + to_string(in2_size - 1) + ":0] IN2," );
  if (create_fin_adder)
    verilog.push ("output logic [" + to_string(out_size - 1) + ":0] result);" );
  else
    {
      verilog.push ("output logic [" + to_string(out_size - 1) + ":0] result0," );
      verilog.push ("output logic [" + to_string(out_size - 1) + ":0] result1);" );
    }
  verilog.push("outdent");
  verilog.push("");

  verilog.push("\n// Creating Partial Products \n");

    bool signed_mult = (pp_encoding[0] == 'S');

  if (pp_encoding.compare ("USP") == 0) {
    create_unsignedpp (in1_size, in2_size, pp_matrix,
                       pp_dim1, pp_dim2, verilog);

  } else if (pp_encoding.compare ("SSP") == 0) {
    create_signedpp (in1_size, in2_size, pp_matrix,
                     pp_dim1, pp_dim2, extra_ones_indices, verilog);
  } else if (pp_encoding.compare ("SB4") == 0) {
    create_br4pp (in1_size, in2_size, true, pp_matrix,
                  pp_dim1, pp_dim2, extra_ones_indices, verilog);
    // create_signedbr4pp (in1_size, in2_size, pp_matrix,
    //                     pp_dim1, pp_dim2, verilog);
  } else if (pp_encoding.compare ("SB8") == 0) {
    create_br8pp (in1_size, in2_size, true, pp_matrix,
                  pp_dim1, pp_dim2, extra_ones_indices, verilog);
  } else if (pp_encoding.compare ("UB8") == 0) {
    create_br8pp (in1_size, in2_size, false, pp_matrix,
                  pp_dim1, pp_dim2, extra_ones_indices, verilog);
  } else if (pp_encoding.compare ("SB16") == 0) {
    create_br16pp (in1_size, in2_size, true, pp_matrix,
                   pp_dim1, pp_dim2, extra_ones_indices, verilog);
  }  else if (pp_encoding.compare ("UB16") == 0) {
    create_br16pp (in1_size, in2_size, false, pp_matrix,
                   pp_dim1, pp_dim2, extra_ones_indices, verilog);
  } else if (pp_encoding.compare ("SB2") == 0) {
    create_br2pp (in1_size, in2_size, true, pp_matrix,
                  pp_dim1, pp_dim2, extra_ones_indices, verilog);
    // create_signedbr2pp (in1_size, in2_size, pp_matrix,
    //                     pp_dim1, pp_dim2, verilog);
  } else if (pp_encoding.compare ("UB2") == 0) {
    create_br2pp (in1_size, in2_size, false, pp_matrix,
                  pp_dim1, pp_dim2, extra_ones_indices, verilog);
    // create_unsignedbr2pp (in1_size, in2_size, pp_matrix,
    //                       pp_dim1, pp_dim2, verilog);
  } else if (pp_encoding.compare ("UB4") == 0) {
    create_br4pp (in1_size, in2_size, false, pp_matrix,
                  pp_dim1, pp_dim2, extra_ones_indices, verilog);
    // create_unsignedbr4pp (in1_size, in2_size, pp_matrix,
    //                       pp_dim1, pp_dim2, verilog);
  } else {
    cout << "Bad PP Selection! Given: " << pp_encoding << endl;
    return 1;
  }

  if (create_fin_adder && !extra_ones_indices.empty()){

    cout << "pp_dim2: " << pp_dim2 << endl;
    for (auto e : extra_ones_indices)
      cout << e << " ";
    cout << endl;

    add_extra_ones_to_pp_matrix (pp_matrix[pp_dim1-1], pp_dim2, extra_ones_indices);
    extra_ones_indices.clear();
  }

  print_pp (pp_matrix, pp_dim1, pp_dim2, verilog, true);

  verilog.push("\n// Creating Summation Tree \n");

  if (tree.compare ("WT") == 0) {
    create_wallacetree (pp_matrix, final_stage_adder, pp_dim1, pp_dim2,
                        out_size,
                        create_fin_adder,
                        signed_mult,
                        verilog,
                        adder_size,
                        zeros_in_output);

  } else if (tree.compare ("DT") == 0){
    create_daddatree (pp_matrix, final_stage_adder, pp_dim1, pp_dim2,
                      out_size,
                      create_fin_adder,
                      signed_mult,
                      verilog,
                      adder_size,
                      zeros_in_output);
  } else {
    cout << "Bad Summation tree Selection!" << endl;
    return 1;
  }

  verilog.push("outdent");

  verilog.push ("endmodule\n\n");

  verilog.push("");

  cout << endl;
  cout << "Multiplier Module (" << module_name << ") is created." << endl;
  cout << "   Inputs: IN1[" << in1_size-1 << ":0], IN2[" << in2_size-1 << ":0]" << endl;
  if (create_fin_adder){
    cout << "   Output: result[" << out_size-1 << ":0]" << endl;
    cout << "   Function: result = IN1 * IN2 " << (signed_mult?"(signed)":"(unsigned)") << endl;
  }else{
    cout << "   Outputs: result0[" << out_size-1 << ":0], result1[" << out_size-1 << ":0]" << endl;
    cout << "   Function: result0+result1 = partial IN1 * IN2 " << (signed_mult?"(signed)":"(unsigned)") << " without complete sign extension." << endl;
  }
  return 0;

}

int create_adder (string final_stage_adder,
                  int adder_size,
                  queue<string>& verilog){

  if (final_stage_adder.compare ("RP") == 0)
    create_rp_adder (adder_size, verilog);
  else if (final_stage_adder.compare ("HC") == 0)
    create_hc_adder (adder_size, verilog);
  else if (final_stage_adder.compare ("LF") == 0)
    create_lf_adder (adder_size, verilog);
  else if (final_stage_adder.compare ("KS") == 0)
    create_ks_adder (adder_size, verilog);
  else{
    cout << "Bad Final Stage Adder Selection!" << endl;
    return 1;
  }

  verilog.push ("module "+final_stage_adder+"_"+to_string(adder_size)+"_spec (");
  verilog.push("indent");
  verilog.push("indent");
  verilog.push ("input logic [" + to_string(adder_size-1) + ":0] IN1,");
  verilog.push ("input logic [" + to_string(adder_size-1) +  ":0] IN2,");
  verilog.push ("output logic adder_correct,");
  verilog.push ("output logic ["  + to_string(adder_size) +  ":0] spec_res);");
  verilog.push("outdent");
  verilog.push("");
  verilog.push("assign spec_res = IN1 + IN2;");
  verilog.push("wire ["  + to_string(adder_size) +  ":0] adder_res;");
  verilog.push(final_stage_adder+"_"+to_string(adder_size) + " adder(IN1, IN2, adder_res);");
  verilog.push("assign adder_correct = ((spec_res == adder_res) ? 1 : 0);");
  verilog.push("");
  verilog.push("outdent");
  verilog.push ("endmodule");
  verilog.push("");

  verilog.push ("\n");

  cout << endl;
  cout << "Adder Module (" << final_stage_adder << "_" << adder_size << ") is created." << endl;
  cout << "   Inputs: IN1[" << adder_size-1 << ":0], IN2[" << adder_size-1 << ":0]" << endl;
  cout << "   Output: result[" <<adder_size << ":0]" << endl;
  cout << "   Function: result=IN1+IN2" << endl;

  return 0;

}

void print_int(string x, std::list<int> const &list)
{
  cout << x << " ";
  for (auto const &i: list) {
    std::cout << i << " ";
  }
  cout << endl;
}

int create_four_mult (int  in_size,
                      int  in3_size,
                      int  out_size,
                      string final_stage_adder,
                      string pp_encoding,
                      string tree,
                      string& module_name,
                      queue<string>& verilog,
                      int& adder_size){

  bool signed_mult = (pp_encoding[0] == 'S');

  //int out_size = max(2*in_size+(in3_size>0?1:0), in3_size+1);
  int in1_size = in_size;
  int in2_size = in_size;

  int one_mult_in_size = (in_size)/2+(signed_mult?1:0);
  int one_mult_out_size = out_size;

  string one_mult_module_name;
  int to_be_ignored;

  std::list<int> extra_ones_indices;

  string FourMultMerger_module_name = "FourMultMerger_"
    + std::string(signed_mult ? "Signed_" : "Unsigned_")
    + to_string(in1_size) + "x"
    + to_string(in2_size)
    + (in3_size>0 ? "_plus_" + to_string(in3_size) : "")
    + (out_size != (max(in1_size+in2_size+(in3_size>0?1:0),in3_size+1)) ? "_" + to_string(out_size) : "" );

  module_name = "Merged_" + tree + "_" + pp_encoding + "_"
    + final_stage_adder + "_"
    + to_string(in1_size) + "x"
    + to_string(in2_size)
    + (in3_size>0 ? "_plus_" + to_string(in3_size) : "")
    + (out_size != (max(in1_size+in2_size+(in3_size>0?1:0),in3_size+1)) ? "_" + to_string(out_size) : "" );

  verilog.push ("");
  verilog.push ("// Specification module to help understand what the design implements.");
  verilog.push ("module "+module_name+"_spec (");
  verilog.push("indent");
  verilog.push("indent");
  verilog.push ("input logic [" + to_string(in1_size-1) + ":0] IN1,");
  verilog.push ("input logic [" + to_string(in2_size-1) +  ":0] IN2,");
  if (in3_size>0)
    verilog.push ("input logic [" + to_string(in3_size-1) +  ":0] IN3,");
  verilog.push ("output logic design_is_correct, // is set to 1 iff the output of " + module_name + "  matches its spec.");
  verilog.push ("output logic ["  + to_string(out_size-1) +  ":0] design_res,");
  verilog.push ("output logic ["  + to_string(out_size-1) +  ":0] spec_res);");
  verilog.push("outdent");
  verilog.push("");
  if (in3_size > 0)
    if (signed_mult)
      verilog.push("assign spec_res = signed'(IN1) * signed'(IN2) + signed'(IN3);");
    else
      verilog.push("assign spec_res = IN1 * IN2 + IN3;");
  else
    if (signed_mult)
      verilog.push("assign spec_res = signed'(IN1) * signed'(IN2);");
    else
      verilog.push("assign spec_res = IN1 * IN2;");

  verilog.push(module_name + " mult(IN1, IN2," + (in3_size>0 ? " IN3," : "")+" design_res);");
  verilog.push("assign design_is_correct = ((spec_res == design_res) ? 1 : 0);");
  verilog.push("");
  verilog.push("outdent");
  verilog.push ("endmodule");
  verilog.push("");

  verilog.push ("\n");

  bool** zeros_in_output = NULL;

  // cout << "1" << endl;

  int retval = create_mult (one_mult_in_size,
                            one_mult_in_size,
                            one_mult_out_size,
                            "",
                            pp_encoding,
                            tree,
                            false,
                            one_mult_module_name,
                            extra_ones_indices,
                            verilog,
                            to_be_ignored,
                            zeros_in_output
                            );

  if (retval!=0)
    return retval;

  // for (int i = 0; i < 2 && zeros_in_output!=NULL; i++){
  //    cout << "zeros_in_output[" << i <<"]: ";
  //    for (auto e : zeros_in_output[i])
  //      cout << e << " ";
  //    cout << endl;
  // }

  //  cout << "2" << endl;

  // -----
  // Create the main module to merge the four multipliers..

  verilog.push ("module " + module_name + "(");
  verilog.push("indent");
  verilog.push("indent");
  verilog.push ("input logic [" + to_string(in1_size - 1) + ":0] IN1," );
  verilog.push ("input logic [" + to_string(in2_size - 1) + ":0] IN2," );
  if (in3_size>0)
    verilog.push ("input logic [" + to_string(in3_size - 1) + ":0] IN3," );
  verilog.push ("output logic [" + to_string(out_size - 1) + ":0] result);" );
  verilog.push("outdent");

  verilog.push ("wire logic [" + to_string(one_mult_out_size-1) + ":0] m1_0;");
  verilog.push ("wire logic [" + to_string(one_mult_out_size-1) + ":0] m1_1;");
  verilog.push ("wire logic [" + to_string(one_mult_out_size-1) + ":0] m2_0;");
  verilog.push ("wire logic [" + to_string(one_mult_out_size-1) + ":0] m2_1;");
  verilog.push ("wire logic [" + to_string(one_mult_out_size-1) + ":0] m3_0;");
  verilog.push ("wire logic [" + to_string(one_mult_out_size-1) + ":0] m3_1;");
  verilog.push ("wire logic [" + to_string(one_mult_out_size-1) + ":0] m4_0;");
  verilog.push ("wire logic [" + to_string(one_mult_out_size-1) + ":0] m4_1;");

  string** pp_matrix;
  int pp_dim1 = 0, pp_dim2 = 0;

  // add the module instantiations for four multipliers.
  if(!signed_mult){

    verilog.push("");
    verilog.push
      (one_mult_module_name + " m1 (IN1["+to_string (one_mult_in_size-1)+":0], " +
       "IN2["+to_string (one_mult_in_size-1)+":0], m1_0, m1_1);");

    verilog.push
      (one_mult_module_name + " m2 (" +

       "IN2["+to_string (one_mult_in_size+one_mult_in_size-1)+":"+
       to_string(one_mult_in_size)+"], "+
       "IN1["+to_string (one_mult_in_size-1)+":0], " +
       "m2_0, m2_1);");

    verilog.push
      (one_mult_module_name + " m3 ("+
       "IN1["+to_string (one_mult_in_size+one_mult_in_size-1)+":"+
       to_string(one_mult_in_size)+"], " +
       " IN2["+to_string (one_mult_in_size-1)+":0], m3_0, m3_1);");

    verilog.push
      (one_mult_module_name + " m4 ("
       +"IN1["+to_string (one_mult_in_size+one_mult_in_size-1)+":"+
       to_string(one_mult_in_size)+"], " +
       ""
       +"IN2["+to_string (one_mult_in_size+one_mult_in_size-1)+":"+
       to_string(one_mult_in_size)+"], m4_0, m4_1);");

    verilog.push("");

  } else {
    verilog.push("");
    verilog.push
      (one_mult_module_name + " m1 ({1'b0, IN1["+to_string (one_mult_in_size-2)+":0]}, " +
       "{1'b0, IN2["+to_string (one_mult_in_size-2)+":0]}, m1_0, m1_1);");

    verilog.push
      (one_mult_module_name + " m2 (" +
       "{IN2["+to_string (one_mult_in_size+one_mult_in_size-3)+"], "+
       "IN2["+to_string (one_mult_in_size+one_mult_in_size-3)+":"+
       to_string(one_mult_in_size-1)+"]}, "+
       "{1'b0, IN1["+to_string (one_mult_in_size-2)+":0]}, " +
       "m2_0, m2_1);");

    verilog.push
      (one_mult_module_name + " m3 ({IN1["+to_string (one_mult_in_size+one_mult_in_size-3)+"], "+
       "IN1["+to_string (one_mult_in_size+one_mult_in_size-3)+":"+
       to_string(one_mult_in_size-1)+"]}, " +
       "{1'b0, IN2["+to_string (one_mult_in_size-2)+":0]}, m3_0, m3_1);");

    verilog.push
      (one_mult_module_name + " m4 ({IN1["+to_string (one_mult_in_size+one_mult_in_size-3)+"],"
       +"IN1["+to_string (one_mult_in_size+one_mult_in_size-3)+":"+
       to_string(one_mult_in_size-1)+"]}, " +
       "{IN2["+to_string (one_mult_in_size+one_mult_in_size-3)+"], "
       +"IN2["+to_string (one_mult_in_size+one_mult_in_size-3)+":"+
       to_string(one_mult_in_size-1)+"]}, m4_0, m4_1);");

    verilog.push("");
  }

  if (!signed_mult){

    pp_dim1 = 10;
    pp_dim2 = out_size;
    pp_matrix = new string*[pp_dim1];

    for (int i = 0; i < pp_dim1; i++)
      pp_matrix[i] = new string[pp_dim2];

    for (int i = 0;  i < pp_dim2; i++){
      if (i<one_mult_out_size){
        if (!zeros_in_output[0][i]) pp_matrix[0][i] = "m1_0[" + to_string(i) + "]";
        if (!zeros_in_output[1][i]) pp_matrix[1][i] = "m1_1[" + to_string(i) + "]";
      }

      if (i>=one_mult_in_size && i<(one_mult_out_size+one_mult_in_size)){
        if (!zeros_in_output[0][i-one_mult_in_size]) pp_matrix[2][i] = "m2_0[" + to_string(i-one_mult_in_size) + "]";
        if (!zeros_in_output[1][i-one_mult_in_size]) pp_matrix[3][i] = "m2_1[" + to_string(i-one_mult_in_size) + "]";
        if (!zeros_in_output[0][i-one_mult_in_size]) pp_matrix[4][i] = "m3_0[" + to_string(i-one_mult_in_size) + "]";
        if (!zeros_in_output[1][i-one_mult_in_size]) pp_matrix[5][i] = "m3_1[" + to_string(i-one_mult_in_size) + "]";
      }

      if (i>= (one_mult_in_size)*2 ){
        if (!zeros_in_output[0][i-one_mult_in_size*2]) pp_matrix[6][i] = "m4_0[" + to_string(i-one_mult_in_size*2) + "]";
        if (!zeros_in_output[1][i-one_mult_in_size*2]) pp_matrix[7][i] = "m4_1[" + to_string(i-one_mult_in_size*2) + "]";
      }

      if (i<in3_size) {
        pp_matrix[8][i] = "IN3["+to_string(i)+"]";
      }

    }

    std::list<int> merged_extra_ones_indices = merge_extra_ones_indices (extra_ones_indices,
                                                                         extra_ones_indices,
                                                                         one_mult_in_size);

    merged_extra_ones_indices = merge_extra_ones_indices (merged_extra_ones_indices,
                                                          extra_ones_indices,
                                                          one_mult_in_size);

    merged_extra_ones_indices = merge_extra_ones_indices (merged_extra_ones_indices,
                                                          extra_ones_indices,
                                                          2*(one_mult_in_size));

    add_extra_ones_to_pp_matrix (pp_matrix[9], out_size, merged_extra_ones_indices);

  } else {

    pp_dim1 = 10;
    pp_dim2 = out_size;
    pp_matrix = new string*[pp_dim1];
    for (int i = 0; i < pp_dim1; i++)
      pp_matrix[i] = new string[pp_dim2];

    for (int i = 0;  i < pp_dim2; i++){

      if (i<one_mult_out_size){
        if (!zeros_in_output[0][i]) pp_matrix[0][i] = "m1_0[" + to_string(i) + "]";
        if (!zeros_in_output[1][i]) pp_matrix[1][i] = "m1_1[" + to_string(i) + "]";
      }

      if (i>=one_mult_in_size-1){
        if ( i<(one_mult_out_size+one_mult_in_size-1)){

          if (!zeros_in_output[0][i-one_mult_in_size+1])
            pp_matrix[2][i] = "m2_0[" + to_string(i-one_mult_in_size+1) + "]";
          if (!zeros_in_output[1][i-one_mult_in_size+1])
            pp_matrix[3][i] =  "m2_1[" + to_string(i-one_mult_in_size+1) + "]";
          if (!zeros_in_output[0][i-one_mult_in_size+1])
            pp_matrix[4][i] = "m3_0[" + to_string(i-one_mult_in_size+1) + "]";
          if (!zeros_in_output[1][i-one_mult_in_size+1])
            pp_matrix[5][i] =  "m3_1[" + to_string(i-one_mult_in_size+1) + "]";
        }
      }
      if (i>=(one_mult_in_size-1)*2) {
        if ( i < pp_dim2){
          if (!zeros_in_output[0][i- (one_mult_in_size-1)*2])
            pp_matrix[6][i] = "m4_0[" + to_string(i- (one_mult_in_size-1)*2) + "]";
          if (!zeros_in_output[1][i- (one_mult_in_size-1)*2])
            pp_matrix[7][i] = "m4_1[" + to_string(i- (one_mult_in_size-1)*2) + "]";
        }
      }

      if (i < in3_size-1){
        pp_matrix[8][i] = "IN3[" + to_string(i) + "]";
      } else if (i==in3_size-1){
        pp_matrix[8][i] = "~IN3[" + to_string(i) + "]";

      }
    }

    std::list<int> merged_extra_ones_indices = merge_extra_ones_indices (extra_ones_indices,
                                                                         extra_ones_indices,
                                                                         one_mult_in_size-1);

    merged_extra_ones_indices = merge_extra_ones_indices (merged_extra_ones_indices,
                                                          extra_ones_indices,
                                                          one_mult_in_size-1);

    merged_extra_ones_indices = merge_extra_ones_indices (merged_extra_ones_indices,
                                                          extra_ones_indices,
                                                          2*(one_mult_in_size-1));
    if (in3_size > 0){
      std::list<int> in3_extra_ones_indices;
      in3_extra_ones_indices.push_back(in3_size-1);
      merged_extra_ones_indices = merge_extra_ones_indices (merged_extra_ones_indices,
                                                            in3_extra_ones_indices,
                                                            0);
    }

    add_extra_ones_to_pp_matrix (pp_matrix[9], out_size, merged_extra_ones_indices);

  }

  print_pp(pp_matrix, pp_dim1, pp_dim2, verilog, true);

  //std::list<int>* zeros_in_output = NULL;
  if (tree.compare("WT") == 0)
    create_wallacetree (pp_matrix,
                        final_stage_adder,
                        pp_dim1,
                        pp_dim2,
                        out_size,
                        true,
                        signed_mult,
                        verilog,
                        adder_size,
                        zeros_in_output);
  else
    create_daddatree (pp_matrix,
                      final_stage_adder,
                      pp_dim1,
                      pp_dim2,
                      out_size,
                      true,
                      signed_mult,
                      verilog,
                      adder_size,
                      zeros_in_output);

  //print_pp(pp_matrix, pp_dim1, pp_dim2);

  verilog.push("outdent");
  verilog.push("");
  verilog.push("endmodule");

  verilog.push("");

  cout << endl;
  cout << "Merged Multiplier Module (" << module_name << ") is created." << endl;
  cout << "   Inputs: IN1[" << in1_size-1 << ":0], IN2[" << in2_size-1 << ":0]";
  if (in3_size>0)
    cout << ", IN3[" << in3_size-1 << ":0]";
  cout << endl;
  cout << "   Output: result[" << out_size-1 << ":0]" << endl;
  if (signed_mult){
    cout << "   Function: result = signed'(IN1) * signed'(IN2) ";
    if (in3_size>0)
      cout << "+ signed'(IN3)";
    cout << endl;
  } else {
    cout << "   Function: result = IN1 * IN2 ";
    if (in3_size>0)
      cout << "+ IN3";
    cout << " (unsigned)" << endl;
  }

  return 0;

}

int create_mac (int  in1_size,
                int  in2_size,
                int  in3_size,
                int  out_size,
                string final_stage_adder,
                string pp_encoding,
                string tree,
                string& module_name,
                queue<string>& verilog,
                int& adder_size){

  bool signed_mult = (pp_encoding[0] == 'S');

  string mult_module_name;
  int to_be_ignored;

  if (in3_size < 1)
    in3_size = 1;

  module_name = "MAC_" + tree + "_" + pp_encoding + "_"
    + final_stage_adder + "_"
    + to_string(in1_size) + "x"
    + to_string(in2_size) + "_plus_"
    + to_string(in3_size)
    + (out_size != max(in2_size+in1_size+1, in3_size+1) ? "_" + to_string(out_size) : "" );

  verilog.push ("");
  verilog.push ("// Specification module to help understand what the design implements.");
    verilog.push ("module "+module_name+"_spec (");
  verilog.push("indent");
  verilog.push("indent");
  verilog.push ("input logic [" + to_string(in1_size-1) + ":0] IN1,");
  verilog.push ("input logic [" + to_string(in2_size-1) +  ":0] IN2,");
  verilog.push ("input logic [" + to_string(in3_size-1) +  ":0] IN3,");
  verilog.push ("output logic design_is_correct, // is set to 1 iff the output of " + module_name + "  matches its spec.");
  verilog.push ("output logic ["  + to_string(out_size-1) +  ":0] design_res,");
  verilog.push ("output logic ["  + to_string(out_size-1) +  ":0] spec_res);");
  verilog.push("outdent");
  verilog.push("");
  if (signed_mult)
    verilog.push("assign spec_res = signed'(IN1) * signed'(IN2) + signed'(IN3);");
  else
    verilog.push("assign spec_res = IN1 * IN2 + IN3;");

  verilog.push(module_name + " mult(IN1, IN2," + (in3_size>0 ? " IN3," : "")+" design_res);");
  verilog.push("assign design_is_correct = ((spec_res == design_res) ? 1 : 0);");
  verilog.push("");
  verilog.push("outdent");
  verilog.push ("endmodule");
  verilog.push("");

  int mult_out_size = min(out_size, max (in1_size+in2_size+1,in3_size+1));

  std::list<int> extra_ones_indices;

  bool** zeros_in_output = NULL;

  int retval = create_mult (in1_size,
                            in2_size,
                            mult_out_size,
                            "",
                            pp_encoding,
                            tree,
                            false,
                            mult_module_name,
                            extra_ones_indices,
                            verilog,
                            to_be_ignored,
                            zeros_in_output);

  if (retval!=0){
    cout << "PROBLEM! create_mult returned " << retval << endl;
    return retval;
  }

  verilog.push ("module " + module_name + "(");
  verilog.push("indent");
  verilog.push("indent");
  verilog.push("input logic [" + to_string(in1_size - 1) + ":0] IN1," );
  verilog.push("input logic [" + to_string(in2_size - 1) + ":0] IN2," );
  verilog.push("input logic [" + to_string(in3_size - 1) + ":0] IN3," );
  verilog.push("output logic [" + to_string(out_size - 1) + ":0] result);" );
  verilog.push("outdent");

  verilog.push ("wire logic [" + to_string(mult_out_size-1) + ":0] m1_0;");
  verilog.push ("wire logic [" + to_string(mult_out_size-1) + ":0] m1_1;");

  verilog.push
    (mult_module_name + " m1 (IN1["+to_string (in1_size-1)+":0], " +
     "IN2["+to_string (in2_size-1)+":0], m1_0, m1_1);");

  verilog.push("");

  string** pp_matrix;
  int pp_dim1 = 0, pp_dim2 = 0;

  if (!signed_mult){

    pp_dim1 = 4;
    pp_dim2 = out_size;
    pp_matrix = new string*[pp_dim1];
    for (int i = 0; i < pp_dim1; i++)
      pp_matrix[i] = new string[pp_dim2];

    for (int i = 0;  i < pp_dim2; i++){
      if (i<mult_out_size){
        if(!zeros_in_output[0][i]) pp_matrix[0][i] = "m1_0[" + to_string(i) + "]";
        if(!zeros_in_output[1][i]) pp_matrix[1][i] = "m1_1[" + to_string(i) + "]";
      }
      if (i < in3_size ){
        pp_matrix[2][i] = "IN3[" + to_string(i) + "]";
      }
    }
  } else {
    pp_dim1 = 4;
    pp_dim2 = out_size;
    pp_matrix = new string*[pp_dim1];
    for (int i = 0; i < pp_dim1; i++)
      pp_matrix[i] = new string[pp_dim2];

    for (int i = 0;  i < pp_dim2; i++){

      if (i < mult_out_size){
        if(!zeros_in_output[0][i]) pp_matrix[0][i] = "m1_0[" + to_string(i) + "]";
        if(!zeros_in_output[1][i]) pp_matrix[1][i] = "m1_1[" + to_string(i) + "]";
      }
      if (i < in3_size-1){
        pp_matrix[2][i] = "IN3[" + to_string(i) + "]";
      } else if (i==in3_size-1){
        pp_matrix[2][i] = "~IN3[" + to_string(i) + "]";

      }
    }

    std::list<int> in3_extra_ones_indices;
    in3_extra_ones_indices.push_back(in3_size-1);
    extra_ones_indices =   merge_extra_ones_indices (extra_ones_indices,
                                                     in3_extra_ones_indices,
                                                     0);

  }

  add_extra_ones_to_pp_matrix (pp_matrix[3], out_size, extra_ones_indices);

  print_pp(pp_matrix, pp_dim1, pp_dim2, verilog, true);

  if (tree.compare("WT") == 0)
    create_wallacetree (pp_matrix,
                        final_stage_adder,
                        pp_dim1,
                        pp_dim2,
                        out_size,
                        true,
                        signed_mult,
                        verilog,
                        adder_size,
                        zeros_in_output);
  else
    create_daddatree (pp_matrix,
                      final_stage_adder,
                      pp_dim1,
                      pp_dim2,
                      out_size,
                      true,
                      signed_mult,
                      verilog,
                      adder_size,
                      zeros_in_output);

  //print_pp(pp_matrix, pp_dim1, pp_dim2);

  verilog.push("outdent");
  verilog.push("");
  verilog.push("endmodule");

  verilog.push("");

  verilog.push("");

  cout << endl;
  cout << "Multiply-Accumulate Module (" << module_name << ") is created." << endl;
  cout << "   Inputs: IN1[" << in1_size-1 << ":0], IN2[" << in2_size-1 << ":0], IN3[" << in3_size-1 << ":0]" << endl;
  cout << "   Output: result[" << out_size-1 << ":0]" << endl;
  if (signed_mult)
    cout << "   Function: result = signed'(IN1) * signed'(IN2) + signed'(IN3) " << endl;
  else
    cout << "   Function: result = IN1 * IN2 + IN3 (unsigned)"  << endl;
  return 0;

}

int create_dot (int  in1_size,
                int  in2_size,
                int  in3_size,
                int  dot_size,
                int  out_size,
                string final_stage_adder,
                string pp_encoding,
                string tree,
                string& module_name,
                queue<string>& verilog,
                int& adder_size){

  bool signed_mult = (pp_encoding[0] == 'S');
  string mult_module_name;
  int to_be_ignored;

  //int  min_Out_size = dot_size*(((1<<in1_size) -1) * ((1<<in2_size) -1)) + ((1<<in3_size) -1);
  //min_Out_size = std::to_string(min_Out_size).length();
  int min_Out_size = max (in3_size+1, in1_size+in2_size + dot_size-1);
  int mult_out_size = min(out_size, min_Out_size);
  out_size = mult_out_size;

  module_name = "DOT_Product_" + tree + "_" + pp_encoding + "_"
    + final_stage_adder + "_"
    + to_string(dot_size) + "_"
    + to_string(in1_size) + "x"
    + to_string(in2_size)
    + (in3_size>0 ? "_plus_" + to_string(in3_size) : "")
    + (out_size != min_Out_size
       ? "_" + to_string(out_size) : "" );

  verilog.push ("");
  verilog.push ("// Specification module to help understand what the design implements.");
  verilog.push ("module "+module_name+"_spec (");
  verilog.push("indent");
  verilog.push("indent");
  verilog.push ("input logic [" + to_string(dot_size-1) + ":0][" + to_string(in1_size-1) + ":0] IN1,");
  verilog.push ("input logic [" + to_string(dot_size-1) + ":0][" + to_string(in2_size-1) +  ":0] IN2,");
  verilog.push ("input logic [" + to_string(in3_size-1) +  ":0] IN3,");
  verilog.push ("output logic design_is_correct, // is set to 1 iff the output of " + module_name + "  matches its spec");
  verilog.push ("output logic ["  + to_string(out_size-1) +  ":0] design_res,");
  verilog.push ("output logic ["  + to_string(out_size-1) +  ":0] spec_res);");
  verilog.push("outdent");
  verilog.push("");
  if (signed_mult){
    string x = "assign spec_res = ";
    for (int i = 0; i<dot_size; i++)
      x += "(signed'(IN1["+to_string(i)+"]) * signed'(IN2["+to_string(i)+"])) + \n\t\t      ";
    verilog.push(x + "signed'(IN3);");
  }else{
    string x = "assign spec_res = ";
    for (int i = 0; i<dot_size; i++)
      x += "(unsigned'(IN1["+to_string(i)+"]) * unsigned'(IN2["+to_string(i)+"])) + \n\t\t      ";
    verilog.push(x + "unsigned'(IN3);");
  }
  verilog.push(module_name + " dot_product(IN1, IN2," + (in3_size>0 ? " IN3," : "")+" design_res);");
  verilog.push("assign design_is_correct = ((spec_res == design_res) ? 1 : 0);");
  verilog.push("");
  verilog.push("outdent");
  verilog.push ("endmodule");
  verilog.push("");

  std::list<int> extra_ones_indices;

  bool** zeros_in_output = NULL;

  int retval = create_mult (in1_size,
                            in2_size,
                            mult_out_size,
                            "",
                            pp_encoding,
                            tree,
                            false,
                            mult_module_name,
                            extra_ones_indices,
                            verilog,
                            to_be_ignored,
                            zeros_in_output
                            );

  if (retval!=0)
    return retval;

  string** pp_matrix;
  int pp_dim1 = 0, pp_dim2 = 0;

  verilog.push ("module " + module_name + "(");
  verilog.push("indent");
  verilog.push("indent");
  verilog.push ("input logic [" + to_string(dot_size-1) + ":0][" + to_string(in1_size-1) + ":0] IN1,");
  verilog.push ("input logic [" + to_string(dot_size-1) + ":0][" + to_string(in2_size-1) +  ":0] IN2,");

  if (in3_size>0)
    verilog.push("input logic [" + to_string(in3_size - 1) + ":0] IN3," );
  verilog.push("output logic [" + to_string(out_size - 1) + ":0] result);" );
  verilog.push("outdent");
  verilog.push("");

  for (int j = 0; j < dot_size; j++){
    string m = "m" + to_string(j);
    verilog.push ("wire logic [" + to_string(mult_out_size-1) + ":0] "+m+"_0;");
    verilog.push ("wire logic [" + to_string(mult_out_size-1) + ":0] "+m+"_1;");
  }

  verilog.push("");

  for (int j = 0; j < dot_size; j++){
    string m = "m" + to_string(j);
    verilog.push
      (mult_module_name + " "+m+" (IN1["+to_string(j)+"]["+to_string (in1_size-1)+":0], " +
       "IN2["+to_string(j)+"]["+to_string (in2_size-1)+":0], "+m+"_0, "+m+"_1);");
  }

  std::list<int> merged_extra_ones_indices = extra_ones_indices;

  if (!signed_mult){

    pp_dim1 = 2+2*dot_size;
    pp_dim2 = out_size;
    pp_matrix = new string*[pp_dim1];
    for (int i = 0; i < pp_dim1; i++)
      pp_matrix[i] = new string[pp_dim2];

    for (int i = 0;  i < pp_dim2; i++){
      if (i < in3_size ){
        pp_matrix[pp_dim1-2][i] = "IN3[" + to_string(i) + "]";
      }
      if (i<mult_out_size){
        for (int j = 0; j < dot_size; j++){
          string m = "m" + to_string(j);
          if(!zeros_in_output[0][i]) pp_matrix[j*2][i] = m + "_0[" + to_string(i) + "]";
          if(!zeros_in_output[1][i]) pp_matrix[j*2+1][i] = m + "_1[" + to_string(i) + "]";
        }
      }
    }
  } else {

    pp_dim1 = 2+2*dot_size;;
    pp_dim2 = out_size;
    pp_matrix = new string*[pp_dim1];
    for (int i = 0; i < pp_dim1; i++)
      pp_matrix[i] = new string[pp_dim2];

    for (int i = 0;  i < pp_dim2; i++){

      if (i < mult_out_size){
        for (int j = 0; j < dot_size; j++){
          string m = "m" + to_string(j);
          if(!zeros_in_output[0][i]) pp_matrix[j*2][i] = m + "_0[" + to_string(i) + "]";
          if(!zeros_in_output[1][i]) pp_matrix[j*2+1][i] = m + "_1[" + to_string(i) + "]";
        }
      }
      if (i < in3_size-1){
        pp_matrix[pp_dim1-2][i] = "IN3[" + to_string(i) + "]";
      } else if (i==in3_size-1){
        pp_matrix[pp_dim1-2][i] = "~IN3[" + to_string(i) + "]";

      }
    }

    std::list<int> in3_extra_ones_indices;
    in3_extra_ones_indices.push_back(in3_size-1);
    merged_extra_ones_indices =   merge_extra_ones_indices (merged_extra_ones_indices,
                                                            in3_extra_ones_indices,
                                                            0);
  }

  for (int j = 1; j < dot_size; j++)
    merged_extra_ones_indices =   merge_extra_ones_indices (merged_extra_ones_indices,
                                                            extra_ones_indices,
                                                            0);
  add_extra_ones_to_pp_matrix (pp_matrix[pp_dim1-1], out_size, merged_extra_ones_indices);

  print_pp(pp_matrix, pp_dim1, pp_dim2, verilog, true);

  if (tree.compare("WT") == 0)
    create_wallacetree (pp_matrix,
                        final_stage_adder,
                        pp_dim1,
                        pp_dim2,
                        out_size,
                        true,
                        signed_mult,
                        verilog,
                        adder_size,
                        zeros_in_output);
  else
    create_daddatree (pp_matrix,
                      final_stage_adder,
                      pp_dim1,
                      pp_dim2,
                      out_size,
                      true,
                      signed_mult,
                      verilog,
                      adder_size,
                      zeros_in_output);

  //print_pp(pp_matrix, pp_dim1, pp_dim2);

  verilog.push("");

  // string ms = "";
  // for (int j = 0; j < dot_size; j++)
  //   ms +=  "m" + to_string(j) + "_0, " + "m" + to_string(j) + "_1, ";
  // //verilog.push (DOT_Merger_module_name + " merger ("+ms+(in3_size>0?" IN3,":"")+" result);");

  verilog.push("outdent");
  verilog.push("");
  verilog.push("endmodule");

  verilog.push("");

  cout << endl;
  cout << "Dot Product Module (" << module_name << ") is created." << endl;
  cout << "   Inputs: IN1[i][" << in1_size-1 << ":0], IN2[i][" << in2_size-1 << ":0] (i from 0 to "+to_string(dot_size-1)+")" <<
    (in3_size>0?+", IN3[" + to_string(in3_size-1) +  ":0]" :"")  << endl;
  cout << "   Output: result[" << out_size-1 << ":0]" << endl;
  cout << "   Function: result = IN1[0]*IN2[0] + ... + IN1["+to_string(dot_size-1)+"]*IN2["+to_string(dot_size-1)+
    "] + IN3 " << (signed_mult?"(signed)":"(unsigned)") << endl;

  return 0;

}

void write_to_file (string file_name,
                    queue<string>& verilog){

  ofstream myfile;

  myfile.open (file_name);

  int indent_count = 0;

  while(!verilog.empty()) {
    string line = verilog.front();
    if (line.compare("indent") == 0)
      indent_count++;
    else if (line.compare("outdent") == 0)
      indent_count--;
    else {
      for (int i = 0; i<indent_count; i++)
        myfile << "    ";
      myfile << line << endl;
    }
    verilog.pop();
  }

  myfile.close();

}

int main(int argc, char **argv) {

  int  in1_size;
  int  in2_size;
  int  in3_size;
  int  dot_size;
  int  out_size;
  string final_stage_adder;
  string pp_encoding;
  string tree;
  string main_type;
  bool signed_mult;
  bool ha_fa_with_gates;
  queue<string> verilog;

  int retval = interact_with_user(argc, argv, in1_size, in2_size, in3_size, dot_size, out_size, signed_mult, ha_fa_with_gates, final_stage_adder,
                     pp_encoding, tree, main_type);

  if (retval==2)
    return 0;
  
  enter_license(verilog);

  int adder_size;
  string module_name;

  int retval0 = 0, retval1 = 0;

  bool create_fin_adder = true;

  if (main_type.compare("StandAlone") == 0){
    std::list<int> extra_ones_indices;
    bool** zeros_in_output = NULL;

    retval0 = create_mult(in1_size, in2_size,
                          out_size,
                          final_stage_adder,
                          pp_encoding,
                          tree,
                          create_fin_adder,
                          module_name,
                          extra_ones_indices,
                          verilog,
                          adder_size,
                          zeros_in_output);
  } else if (main_type.compare("FourMult") == 0) {
    create_four_mult (in1_size, in3_size,
                      out_size,
                      final_stage_adder,
                      pp_encoding,
                      tree,
                      module_name,
                      verilog,
                      adder_size);

  } else if (main_type.compare("MAC") == 0){
    create_mac (in1_size,
                in2_size,
                in3_size,
                out_size,
                final_stage_adder,
                pp_encoding,
                tree,
                module_name,
                verilog,
                adder_size);
  } else if (main_type.compare("DOT") == 0){
    create_dot (in1_size,
                in2_size,
                in3_size,
                dot_size,
                out_size,
                final_stage_adder,
                pp_encoding,
                tree,
                module_name,
                verilog,
                adder_size);
  } else if (main_type.compare("Adder") == 0) {
    create_fin_adder = true;
    module_name = final_stage_adder + "_" + to_string (in1_size);
    adder_size = in1_size;
  } else {
    cout << "not implemented yet!" << endl;
    return 1;
  }

  if (create_fin_adder){
    retval1 = create_adder(final_stage_adder, adder_size, verilog);
  }
  if (retval0 == 1 || retval0 == 1)
    return 1;

  create_ha_fa (ha_fa_with_gates, verilog);

  string file_name = module_name + "_multgen.sv";
  write_to_file(file_name, verilog);

  cout << endl;
  cout << "Written to " << file_name << endl;
  cout << endl;

  return 0;
}
