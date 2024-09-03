library ieee;
use ieee.std_logic_1164.all;

entity Mux is
  port (
    In1 : in std_logic_vector(15 downto 0);
    In2 : in std_logic_vector(15 downto 0);
    In3 : in std_logic_vector(15 downto 0);
    In4 : in std_logic_vector(15 downto 0);
    OutMux : out std_logic_vector(15 downto 0);
    MuxSel : in std_logic_vector(1 downto 0)
    );
end Mux;

architecture Behavioral of Mux is
begin

with MuxSel select
    OutMux <= In1 when "00",
              In2 when "01",
              In3 when "10",
              In4 when "11";
              
end Behavioral;