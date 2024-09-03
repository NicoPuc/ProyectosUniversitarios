library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity FFD is
    Port (
        D : in STD_LOGIC;
        C : in STD_LOGIC;
        Q : out STD_LOGIC
    );
end FFD;

architecture Behavioral of FFD is

    signal Q_reg : STD_LOGIC := '0';  -- Internal Q register

begin

    -- Process for rising edge detection
    process (C)
    begin
        if rising_edge(C) then
            Q_reg <= D;
        end if;
    end process;

    -- Output Q
    Q <= Q_reg;

end Behavioral;