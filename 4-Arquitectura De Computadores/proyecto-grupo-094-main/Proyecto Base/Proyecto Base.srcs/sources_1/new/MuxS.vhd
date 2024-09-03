library ieee;
use ieee.std_logic_1164.all;

entity MuxS is
  port (
    In1 : in std_logic_vector(11 downto 0);
    In2 : in std_logic_vector(11 downto 0);
    In3 : in std_logic_vector(11 downto 0);
    OutMux : out std_logic_vector(11 downto 0);
    MuxSel : in std_logic_vector(1 downto 0)
    );
end MuxS;

architecture Behavioral of MuxS is
begin

with MuxSel select
    OutMux <= In1 when "00",
              In2 when "01",
              In3 when others;              
end Behavioral;
