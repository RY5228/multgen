

#include <iostream>
#include <queue>          // std::queue
#include <fstream>

using namespace std;

#include "adders.h"

#include "pp_gen.h"

#include "wallace.h"

void print_strings (string* s, int size){
  for (int i = 0; i<size; i++)
    cout << s[i] << endl;
}

int main() {
  string** pp_matrix;

  int  in1_size = 1024;
  int  in2_size = 1024;
  string final_stage_adder = "RP";
  string pp_encoding = "USP";
  string tree = "WT";

  int pp_dim1, pp_dim2;

  queue<string> verilog;
  int adder_size;

  create_ha_fa (verilog);

  string module_name = tree + "_" + pp_encoding + "_"
		+ final_stage_adder + "_"
		+ to_string(in1_size) + "_"
		+ to_string(in2_size);

  verilog.push ("module " + module_name + "(");
  verilog.push ("input logic [" + to_string(in1_size - 1) + ":0] IN1," );
  verilog.push ("input logic [" + to_string(in2_size - 1) + ":0] IN2," );
  verilog.push ("output logic [" + to_string(in2_size + in1_size - 1) + ":0] result);" );

  verilog.push("\n// Creating Partial Products \n");
  
  if (pp_encoding.compare ("USP") == 0) {
    create_unsignedpp (in1_size, in2_size, pp_matrix,
		      pp_dim1, pp_dim2, verilog);
  } else if (pp_encoding.compare ("SB4") == 0) {
    create_signedbr4pp (in1_size, in2_size, pp_matrix,
		      pp_dim1, pp_dim2, verilog);
  }
    

  
  
  verilog.push("\n// Creating Summation Tree \n");
  create_wallacetree (pp_matrix, final_stage_adder, pp_dim1, pp_dim2,
		      in1_size + in2_size,
		      verilog,
		      adder_size);
  verilog.push ("endmodule\n");

  create_rp_adder (adder_size, verilog);

  ofstream myfile;
  string file_name = module_name + "_multgen.sv";

  myfile.open (file_name);

  while(!verilog.empty()) {
    myfile << verilog.front() << endl;
    verilog.pop();
  }

  myfile.close();

  cout << "Written to " << file_name << " with adder size = " << adder_size << "\n";

  return 0;
}
