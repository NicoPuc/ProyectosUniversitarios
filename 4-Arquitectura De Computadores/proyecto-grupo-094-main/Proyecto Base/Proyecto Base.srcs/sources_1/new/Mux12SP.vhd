library ieee;
use ieee.std_logic_1164.all;

entity Mux12SP is
  port (
    In1 : in std_logic_vector(11 downto 0);
    In2 : in std_logic_vector(11 downto 0);
    In3 : in std_logic_vector(11 downto 0);
    OutMux : out std_logic_vector(11 downto 0);
    MuxSel : in std_logic_vector(1 downto 0)
    );
end Mux12SP;

architecture Behavioral of Mux12SP is
begin

with MuxSel select
    OutMux <= In1 when "10", -- add 1, incSP = 1 y decSP = 0
              In2 when "01", -- restar 1, incSP = 0 y decSP = 1
              In3 when others;  -- 0, 
end Behavioral;