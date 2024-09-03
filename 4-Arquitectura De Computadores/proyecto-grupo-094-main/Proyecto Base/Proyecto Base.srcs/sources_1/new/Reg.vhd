library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Reg is
    Port ( 
        clock   : in  std_logic;
        clear   : in  std_logic;
        load    : in  std_logic;
        datain  : in  std_logic_vector (15 downto 0);
        dataout : out std_logic_vector (15 downto 0)
    );
end Reg;

architecture Behavioral of Reg is

    component FFD
        Port (
            D : in  STD_LOGIC;
            C : in  STD_LOGIC;
            Q : out STD_LOGIC
        );
    end component;

    signal Q : std_logic_vector (15 downto 0);
    signal D_input : std_logic_vector (15 downto 0);
    signal clearmuxout : std_logic_vector (15 downto 0); ---- NUEVA LINEA
    
begin

    -- Asignaci�n condicional para D_input
    D_input <= clearmuxout when load = '1' else Q;  ----- CAMBIE LINEA

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
    inst_FFD13: FFD port map(
        D => D_input(12),
        C => clock,
        Q => Q(12)
    );
    inst_FFD14: FFD port map(
        D => D_input(13),
        C => clock,
        Q => Q(13)
    );
    inst_FFD15: FFD port map(
        D => D_input(14),
        C => clock,
        Q => Q(14)
    );
    inst_FFD16: FFD port map(
        D => D_input(15),
        C => clock,
        Q => Q(15)
    );
    
with clear select
    clearmuxout <= datain when '0', ----- CAMBIE LINEA
    "0000000000000000" when '1';---

dataout <= Q;
end Behavioral;