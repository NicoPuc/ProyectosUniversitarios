library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ALU is
    Port ( a        : in  std_logic_vector (15 downto 0);   -- Primer operando.
           b        : in  std_logic_vector (15 downto 0);   -- Segundo operando.
           sop      : in  std_logic_vector (2 downto 0);   -- Selector de la operaci�n.
           c        : out std_logic;                       -- Se�al de 'carry'.
           z        : out std_logic;                       -- Se�al de 'zero'.
           n        : out std_logic;                       -- Se�al de 'nagative'.
           result   : out std_logic_vector (15 downto 0));  -- Resultado de la operaci�n.
end ALU;

architecture Behavioral of ALU is

component Adder16
    Port ( a  : in  std_logic_vector (15 downto 0);
           b  : in  std_logic_vector (15 downto 0);
           ci : in  std_logic;
           s  : out std_logic_vector (15 downto 0);
           co : out std_logic);
end component;

signal alu_result   : std_logic_vector(15 downto 0);
signal adder_result   : std_logic_vector(15 downto 0);
signal adder_b   : std_logic_vector(15 downto 0);
signal ci_ad   : std_logic;
signal co_ad   : std_logic;

begin

-- Sumador/Restaror
ci_ad <= sop(0) and not(sop(1)) and not(sop(2));

with ci_ad select 
    adder_b <=  b       when '0',
                not(b)  when '1';
           
inst_Adder16: Adder16 port map(
        a      => a,
        b      => adder_b,
        ci     => ci_ad,
        s      => adder_result,
        co     => co_ad
    );       
-- Resultado de la Operaci�n
               
with sop select
    alu_result <= adder_result          when "000", --ADD
                  adder_result          when "001", --SUB
                  a and b               when "010", --AND
                  a or b                when "011", --OR
                  a xor b               when "100", --XOR
                  not(a)                when "101", --NOT
                  '0'& a(15 downto 1)   when "110", --SHR
                  a(14 downto 0) & '0'  when "111"; --SHL
                  
result  <= alu_result;

-- Flags c z n
             
with sop select
    c <=    co_ad    when "000",
            co_ad    when "001",
            a(0)     when "110",
            a(15)    when "111",
            '0'      when others;
      
with alu_result select
    z <= '1'    when "0000000000000000",
         '0'    when others; 

with sop select
    n <= not(co_ad) when "001",
         '0'         when others;      
    

end Behavioral;
