library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;

entity SP is
    Port ( clock : in STD_LOGIC;
           clear : in STD_LOGIC;
           load : in STD_LOGIC;
           incSP : in STD_LOGIC;
           decSP : in STD_LOGIC;
           dataout : out STD_LOGIC_VECTOR (11 downto 0));
end SP;

architecture Behavioral of SP is

    component Reg12
        Port (
            clock   : in  std_logic;
            clear   : in  std_logic;
            load    : in  std_logic;
            datain  : in  std_logic_vector (11 downto 0);
            dataout : out std_logic_vector (11 downto 0)
        );
    end component;

    component Mux12SP
        port (
          In1 : in std_logic_vector(11 downto 0);
          In2 : in std_logic_vector(11 downto 0);
          In3 : in std_logic_vector(11 downto 0);
          OutMux : out std_logic_vector(11 downto 0);
          MuxSel : in std_logic_vector(1 downto 0)
          );
      end component;

      component Adder12SP
        Port ( 
               a  : in  std_logic_vector (11 downto 0);
               b  : in  std_logic_vector (11 downto 0);
               ci : in  std_logic;
               s  : out std_logic_vector (11 downto 0);
               co : out std_logic
               );
    end component;

    signal mux_out : std_logic_vector (11 downto 0);
    signal adder_out : std_logic_vector (11 downto 0);
    ---signal reg_out : std_logic_vector (11 downto 0); -- REVISAR
    signal reg_out : std_logic_vector(11 downto 0) := (others => '1'); -- SI HAY ERRORES CON SP, REEMPLAZAR LINEA DE ARRIBA POR ESTA 
    signal muxfinal : std_logic_vector (11 downto 0); --- MUXCLEAR

    signal dummySignal : std_logic;
    signal concat : std_logic_vector (1 downto 0);

begin
    concat <= incSP & decSP;

    inst_Mux: Mux12SP port map(
    In1 => "000000000001",
    In2 => "111111111111",
    In3 => "000000000000",
    OutMux => mux_out,
    MuxSel => concat
    );

    inst_Adder: Adder12SP port map(
    a  => reg_out,
    b  => mux_out,
    ci => '0',
    s  => adder_out,
    co => dummySignal
    );

    inst_reg: Reg12 port map(
    clock  => clock,
    clear  => clear,
    load   => '1',
    datain => muxfinal, ---- CAMBIE LINEA
    dataout => reg_out
    );

-- MUX S para RAM
with clear select
        muxfinal <= adder_out when '0', ---- CAMBIE LINEA
            "111111111111" when '1';
                    
        
dataout <= reg_out;      ---- CAMBIE LINEA                              

end Behavioral;




