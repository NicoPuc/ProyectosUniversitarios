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
    signal notQ  : STD_LOGIC; -- Internal signal to hold the state of the latch
    signal Q2   : STD_LOGIC;  -- a copy of the Q output
begin
    -- Latch behavior using concurrent signal assignments
    Q <= Q2 ;
    Q2 <= R nor notQ;
    notQ <= S nor Q2;
end Behavioral;