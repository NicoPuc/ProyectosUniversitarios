library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Status is
    Port (
        clock: in STD_LOGIC;
        clear : in STD_LOGIC;
        c : in STD_LOGIC;
        z : in STD_LOGIC;
        n : in STD_LOGIC;
        load : in STD_LOGIC;
        dataout : out STD_LOGIC_VECTOR(2 downto 0)
    );
end Status;

architecture Behavioral of Status is
    component REG
        port ( clock : in STD_LOGIC;
               load : in STD_LOGIC;
               clear : in STD_LOGIC;
               datain : in STD_LOGIC_VECTOR(15 downto 0);
               dataout : out STD_LOGIC_VECTOR(15 downto 0)
    );
    end component; 
    component Adder16
        port( A: in STD_LOGIC_VECTOR(15 downto 0);
              B: in STD_LOGIC_VECTOR(15 downto 0);
              ci : in STD_LOGIC;
              S : out STD_LOGIC_VECTOR(15 downto 0);
              co : out STD_LOGIC
              );
     end component;

signal reg_result : STD_LOGIC_VECTOR(15 downto 0);
signal mux_r : STD_LOGIC_VECTOR(15 downto 0);
signal add_r : STD_LOGIC_VECTOR(15 downto 0);
signal cout : STD_LOGIC;
     
begin
    inst_Adder : Adder16 port map(
        A => reg_result,
        B => "0000000000000001",
        ci => '0',
        s => add_r,
        co => cout
    );
    inst_REG : REG port map(
        clock => clock,
        load => '1',
        clear => clear,
        datain => mux_r,
        dataout => reg_result
     );
with load select
    mux_r <= add_r when '0',
            "0000000000000" & c & z & n when '1';
            
dataout <= reg_result(2 downto 0);
end Behavioral;