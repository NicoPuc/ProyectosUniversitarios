library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Reg_16bitA is
    Port ( clock   : in  std_logic;                       -- Clock signal
           clear   : in  std_logic;                       -- Reset signal
           load    : in  std_logic;                       -- Load signal
                      datain  : in  std_logic_vector (15 downto 0);  -- Data input
           dataout : out std_logic_vector (15 downto 0)  -- Data output
    );
end Reg_16bitA;

architecture Behavioral of Reg_16bitA is

    component FFD
        Port (
            D : in STD_LOGIC;
            C : in STD_LOG_LOGIC;
            Q : out STD_LOGIC
        );
    end component;

begin 
inst_FFD1: FFD port map(
    D => datain(0),
    C => clock,
    Q => dataout(0)
);
inst_FFD2: FFD port map(
    D => datain(1),
    C => clock,
    Q => dataout(1)
);
inst_FFD3: FFD port map(
    D => datain(2),
    C => clock,
    Q => dataout(2)
);
inst_FFD4: FFD port map(
    D => datain(3),
    C => clock,
    Q => dataout(3)
);
inst_FFD5: FFD port map(
    D => datain(4),
    C => clock,
    Q => dataout(4)
);
inst_FFD6: FFD port map(
    D => datain(5),
    C => clock,
    Q => dataout(5)
);
inst_FFD7: FFD port map(
    D => datain(6),
    C => clock,
    Q => dataout(6)
);
inst_FFD8: FFD port map(
    D => datain(7),
    C => clock,
    Q => dataout(7)
);
inst_FFD9: FFD port map(
    D => datain(8),
    C => clock,
    Q => dataout(8)
);
inst_FFD10: FFD port map(
    D => datain(9),
    C => clock,
    Q => dataout(9)
);
inst_FFD11: FFD port map(
    D => datain(10),
    C => clock,
    Q => dataout(10)
);
inst_FFD12: FFD port map(
    D => datain(11),
    C => clock,
    Q => dataout(11)
);
inst_FFD13: FFD port map(
    D => datain(12),
    C => clock,
    Q => dataout(12)
);
inst_FFD14: FFD port map(
    D => datain(13),
    C => clock,
    Q => dataout(13)
);
inst_FFD15: FFD port map(
    D => datain(14),
    C => clock,
    Q => dataout(14)
);
inst_FFD16: FFD port map(
    D => datain(15),
    C => clock,
    Q => dataout(15)
);

with load select D1 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D2 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D3 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D4 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D5 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D6 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D7 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D8 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D9 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D10 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D11 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D12 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D13 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D14 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D15 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';
with load select D16 =<
    not clear and '0' when '0',
    not clear and datain(0) when '1';

  
end Behavioral;

