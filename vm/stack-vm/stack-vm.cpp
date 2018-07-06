#include "stack-vm.h"

//functions
//instruction format
//header:2 bits
//data: 20 bits
//
//header format:
//0 ==> POSITIVE INTEGER
//1 ==> PRIMITIVE INSTRUCTION
//2 ==> NEGATICE INTEGER
//3 ==> UNDEFINED
StackVM::StackVM()
{
memory.reserve(1000000);
}
i32 StackVM::getType(i32 instruction)
{
i32 type=0xc0000000;
type = (type & instruction) >> 30;
return type;
}

i32 StackVM::getData(i32 instruction)
{
i32 data =0x3fffffff;
data = data & instruction;
return data;
}

void StackVM::fetch()
{
pc++;

}



void StackVM::decode()

{

	typ = getType(memory[pc]);
        data = getData(memory[pc]);

}

void StackVM::execute()
{
if (typ == 0 || typ ==2)
{
sp++;
memory[sp] =data;
}
else

{
doPrimitive();

}

}

void StackVM::doPrimitive()
{
switch(data)
{
	case 0: //halt
	      std::cout<<"Halt"<<std::endl;
	      running=0;
	      break;
	case 1:

	      std::cout<<"add"<<memory[sp-1]<<" "<< memory[sp] << std::endl;		     //add
	     memory[sp-1] = memory[sp-1] + memory[sp];
	     sp--;
	     break;

	 case 2:
             std::cout<<"Subtract "<<memory[sp-1]<<" "<< memory[sp] << std::endl;                  //add
             memory[sp-1] = memory[sp-1] - memory[sp];
             sp--;
             break;

          case 3:
             std::cout<<"Multiply "<<memory[sp-1]<<" "<< memory[sp] << std::endl;                  //add
             memory[sp-1] = memory[sp-1] * memory[sp];
             sp--;
             break;
           
	  case 4:
             std::cout<<"divide "<<memory[sp-1]<<" "<< memory[sp] << std::endl;                  //add
             memory[sp-1] = memory[sp-1] /  memory[sp];
             sp--;
             break;


}


}
void StackVM::run()
{
pc -=1;
while(running==1)
{
fetch();
decode();
execute();
std::cout<< "tos :" <<memory[sp] <<std::endl;
}


}


void StackVM::loadProgram(std::vector<i32> prog){

	for(i32 i =0;i<prog.size();i++)
	{
memory[pc + i] = prog[i];
	}
}


