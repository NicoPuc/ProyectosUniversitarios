library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Reg12 is
    Port ( 
        clock   : in  std_logic;
        clear   : in  std_logic;
        load    : in  std_logic;
        datain  : in  std_logic_vector (11 downto 0);
        dataout : out std_logic_vector (11 downto 0)
    );
end Reg12;

architecture Behavioral of Reg12 is

    component FFD
        Port (
            D : in  STD_LOGIC;
            C : in  STD_LOGIC;
            Q : out STD_LOGIC
        );
    end component;

    signal Q : std_logic_vector (11 downto 0);
    signal D_input : std_logic_vector (11 downto 0);

begin

    -- Asignaci�n condicional para D_input
    D_input <= datain when load = '1' else Q;

    -- Instanciaci�n de los flip-flops D
    inst_FFD1: FFD port map(
    D => D_input(0),
    C => clock,
    Q => Q(0)
    );
    inst_FFD2: FFD port map(
        D => D_input(1),
        C => clock,
        Q => Q(1)
    );
    inst_FFD3: FFD port map(
        D => D_input(2),
        C => clock,
        Q => Q(2)
    );
    inst_FFD4: FFD port map(
        D => D_input(3),
        C => clock,
        Q => Q(3)
    );
    inst_FFD5: FFD port map(
        D => D_input(4),
        C => clock,
        Q => Q(4)
    );
    inst_FFD6: FFD port map(
        D => D_input(5),
        C => clock,
        Q => Q(5)
    );
    inst_FFD7: FFD port map(
        D => D_input(6),
        C => clock,
        Q => Q(6)
    );
    inst_FFD8: FFD port map(
        D => D_input(7),
        C => clock,
        Q => Q(7)
    );
    inst_FFD9: FFD port map(
        D => D_input(8),
        C => clock,
        Q => Q(8)
    );
    inst_FFD10: FFD port map(
        D => D_input(9),
        C => clock,
        Q => Q(9)
    );
    inst_FFD11: FFD port map(
        D => D_input(10),
        C => clock,
        Q => Q(10)
    );
    inst_FFD12: FFD port map(
        D => D_input(11),
        C => clock,
        Q => Q(11)
    );
    dataout <= Q;

end Behavioral;