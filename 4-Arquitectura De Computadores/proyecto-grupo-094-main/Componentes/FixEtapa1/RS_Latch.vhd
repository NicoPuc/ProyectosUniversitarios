library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity RS_Latch is
    Port (
        R : in STD_LOGIC;     -- Reset input
        S : in STD_LOGIC;     -- Set input
        Q : out STD_LOGIC    -- Output Q
    );
end RS_Latch;

architecture Behavioral of RS_Latch is
    signal Qt       :   STD_LOGIC;
    signal notQ       :   STD_LOGIC;
begin
    -- Latch behavior using concurrent signal assignments
    
Q <= Qt;
Qt <= R nand notQ;
notQ <= S nand Qt;

end Behavioral;