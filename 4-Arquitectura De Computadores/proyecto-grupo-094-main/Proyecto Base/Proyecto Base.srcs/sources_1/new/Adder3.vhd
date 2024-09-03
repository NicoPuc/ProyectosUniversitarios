library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Adder3 is
    Port ( a  : in  std_logic_vector (2 downto 0);
           b  : in  std_logic_vector (2 downto 0);
           ci : in  std_logic;
           s  : out std_logic_vector (2 downto 0);
           co : out std_logic);
end Adder3;

architecture Behavioral of Adder3 is

component FA
    Port ( a  : in  std_logic;
           b  : in  std_logic;
           ci : in  std_logic;
           s  : out std_logic;
           co : out std_logic);
    end component;

signal c : std_logic_vector(1 downto 0);

begin

inst_FA0: FA port map(
        a      =>a(0),
        b      =>b(0),
        ci     =>ci,
        s      =>s(0),
        co     =>c(0)
    );
    
inst_FA1: FA port map(
        a      =>a(1),
        b      =>b(1),
        ci     =>c(0),
        s      =>s(1),
        co     =>c(1)
    );

inst_FA2: FA port map(
        a      =>a(2),
        b      =>b(2),
        ci     =>c(1),
        s      =>s(2),
        co     =>co
    );
    
end Behavioral;