library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ControlUnit is
    Port ( from_status : in STD_LOGIC_VECTOR (2 downto 0);
           from_rom : in STD_LOGIC_VECTOR (19 downto 0);
           enableA : out STD_LOGIC; --carga A
           enableB : out STD_LOGIC; --carga B
           selA : out STD_LOGIC_VECTOR (1 downto 0);
           selB : out STD_LOGIC_VECTOR (1 downto 0);
           loadPC : out STD_LOGIC;
           selALU : out STD_LOGIC_VECTOR (2 downto 0);
           selPC : out STD_LOGIC;
           selRAM_datain : out STD_LOGIC;
           selRAM_address: out STD_LOGIC_VECTOR (1 downto 0);
           incSP: out STD_LOGIC;
           decSP: out STD_LOGIC;
           w: out STD_LOGIC);
end ControlUnit;

architecture Behavioral of ControlUnit is

signal jmp_cond : std_logic;

begin

--010011000000

enableA <= from_rom(15);

with from_rom(14) select
    enableB  <=   '0'     when '0', --
                  '1'     when '1', --
                  '0'     when others;

selA  <=    from_rom (13 downto 12);
selB  <=    from_rom (11 downto 10);

with from_rom (9 downto 7) select
    -- MOV "000" -- ADD "000" -- SUB "001" -- AND "010" -- OR "011"
    -- XOR "100" -- NOT "101" -- SHR "110" -- SHL "111"
                                
    selALU <=   "000"     when "000", --
                "001"     when "001", 
                "010"     when "010", --
                "011"     when "011", 
                "100"     when "100", --
                "101"     when "101", 
                "110"     when "110", --
                "111"     when "111",
                "000"     when others;

with from_rom(6) select              
    w  <=       '0'     when '0', --
                '1'     when '1', --
                '0'     when others;

        
with from_rom(5) select              
    jmp_cond  <=    '1'     when '1', --JMP
                    '0'     when others;

with from_rom (19 downto 16) select              
    loadPC  <=    jmp_cond                         when "0001", --JMP Ins
                  jmp_cond and from_status(1)      when "0010", --JEQ Ins
                  jmp_cond and not(from_status(1)) when "0011", --JNE INS
                  jmp_cond and not(from_status(0)) and  not(from_status(1)) when "1000", --JGT Ins
                  jmp_cond and not(from_status(0)) when "1001", --JGE
                  jmp_cond and from_status(0)      when "1010", --JLT
                  jmp_cond and (from_status(0) or from_status(1)) when "1011", --JLE
                  jmp_cond and from_status(2)      when "1100", --JCR
                  jmp_cond     when "0000",
                  '0' when others;
       

selRAM_address <= from_rom(4 downto 3);

decSP <= from_rom(1);
incSP <= from_rom(2);

with from_rom(0) select

    selPC <= '0' when '0',
             '1' when others;


with from_rom(19 downto 0) select

    selRAM_datain <= '1' when "00000000000001100010",
                     '0' when others;
                     
end Behavioral;