library ieee;
use ieee.std_logic_1164.all;

entity MuxDatain is
  port (
    In1 : in std_logic_vector(15 downto 0);
    In2 : in std_logic_vector(15 downto 0);
    OutMux : out std_logic_vector(15 downto 0);
    MuxSel : in std_logic
    );
end MuxDatain;

architecture Behavioral of MuxDatain is
begin

with MuxSel select
    OutMux <= In1 when '0',
              In2 when '1',
              (others => '0') when others; 

end Behavioral;