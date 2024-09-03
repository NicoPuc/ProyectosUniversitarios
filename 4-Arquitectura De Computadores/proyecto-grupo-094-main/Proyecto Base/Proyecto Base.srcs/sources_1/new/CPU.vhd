library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.numeric_std.all;


entity CPU is
    Port (
           clock : in STD_LOGIC;
           clear : in STD_LOGIC;
           ram_address : out STD_LOGIC_VECTOR (11 downto 0);
           ram_datain : out STD_LOGIC_VECTOR (15 downto 0);
           ram_dataout : in STD_LOGIC_VECTOR (15 downto 0);
           ram_write : out STD_LOGIC;
           rom_address : out STD_LOGIC_VECTOR (11 downto 0);
           rom_dataout : in STD_LOGIC_VECTOR (35 downto 0);
           dis : out STD_LOGIC_VECTOR (15 downto 0));
end CPU;

architecture Behavioral of CPU is

component Reg
    Port ( clock    : in  std_logic;                        -- Se?al del clock (reducido).
           clear    : in  std_logic;                        -- Se?al de reset.
           load     : in  std_logic;                        -- Se?al de carga.
           datain   : in  std_logic_vector (15 downto 0);   -- Se?ales de entrada de datos.
           dataout  : out std_logic_vector (15 downto 0));  -- Se?ales de salida de datos.
end component;

component ALU
    Port ( a        : in  std_logic_vector (15 downto 0);   -- Primer operando.
           b        : in  std_logic_vector (15 downto 0);   -- Segundo operando.
           sop      : in  std_logic_vector (2 downto 0);   -- Selector de la operaci?n.
           c        : out std_logic;                       -- Se?al de 'carry'.
           z        : out std_logic;                       -- Se?al de 'zero'.
           n        : out std_logic;                       -- Se?al de 'nagative'.
           result   : out std_logic_vector (15 downto 0));  -- Resultado de la operaci?n.
end component;

component Status
    Port ( clock : in STD_LOGIC;
           clear : in STD_LOGIC;
           load : in std_logic;
           c : in STD_LOGIC;
           z : in STD_LOGIC;
           n : in STD_LOGIC;
           dataout : out STD_LOGIC_VECTOR (2 downto 0));
end component;

component PC
    Port ( clock : in STD_LOGIC;
           clear : in STD_LOGIC;
           load : in STD_LOGIC;
           datain : in STD_LOGIC_VECTOR (11 downto 0);
           dataout : out STD_LOGIC_VECTOR (11 downto 0));
end component;

component ControlUnit
    Port ( from_status : in STD_LOGIC_VECTOR (2 downto 0);
           from_rom : in STD_LOGIC_VECTOR (19 downto 0);
           enableA : out STD_LOGIC; --carga A
           enableB : out STD_LOGIC; --carga B
           selA : out STD_LOGIC_VECTOR (1 downto 0);
           selB : out STD_LOGIC_VECTOR (1 downto 0);
           loadPC : out STD_LOGIC;
           selALU : out STD_LOGIC_VECTOR (2 downto 0);
           SelPC : out STD_LOGIC;
           selRAM_datain : out STD_LOGIC;
           incSP: out STD_LOGIC;
           decSP: out STD_LOGIC;
           selRAM_address: out STD_LOGIC_VECTOR (1 downto 0);
           w: out STD_LOGIC);
           
end component;

----- componentes e2

component Adder12
       Port ( a  : in  std_logic_vector (11 downto 0);
              b  : in  std_logic_vector (11 downto 0);
              ci : in  std_logic;
              s  : out std_logic_vector (15 downto 0);
              co : out std_logic);
   end component;

component MuxDatain
       port (
         In1 : in std_logic_vector(15 downto 0);
         In2 : in std_logic_vector(15 downto 0);
         OutMux : out std_logic_vector(15 downto 0);
         MuxSel : in std_logic
         );
end component;

component MuxPC
       port (
         In1 : in std_logic_vector(11 downto 0);
         In2 : in std_logic_vector(11 downto 0);
         OutMux : out std_logic_vector(11 downto 0);
         MuxSel : in std_logic
         );
end component;

component MuxS
       port (
         In1 : in std_logic_vector(11 downto 0);
         In2 : in std_logic_vector(11 downto 0);
         In3 : in std_logic_vector(11 downto 0);
         OutMux : out std_logic_vector(11 downto 0);
         MuxSel : in std_logic_vector(1 downto 0)
         );
end component;

component SP
       Port ( clock : in STD_LOGIC;
              clear : in STD_LOGIC;
              load : in STD_LOGIC;
              incSP : in STD_LOGIC;
              decSP : in STD_LOGIC;
              dataout : out STD_LOGIC_VECTOR (11 downto 0));
   end component;


signal write: STD_LOGIC;
signal enableA : STD_LOGIC;
signal enableB : STD_LOGIC;
signal loadPC : STD_LOGIC;
signal alu_result : STD_LOGIC_VECTOR (15 downto 0);
signal regA_result : STD_LOGIC_VECTOR (15 downto 0);
signal regB_result : STD_LOGIC_VECTOR (15 downto 0);
signal selA : STD_LOGIC_VECTOR (1 downto 0);
signal selB : STD_LOGIC_VECTOR (1 downto 0);
signal muxA_result : STD_LOGIC_VECTOR (15 downto 0);
signal muxB_result : STD_LOGIC_VECTOR (15 downto 0);
signal sop_signal: STD_LOGIC_VECTOR (2 downto 0);
signal sigc: std_logic;
signal sigz: std_logic;
signal signn: std_logic;
signal from_status: STD_LOGIC_VECTOR (2 downto 0);
-- señales e2

-- Senales SP
signal incSP  : STD_LOGIC;
signal decSP  : STD_LOGIC;
signal SP_out : STD_LOGIC_VECTOR(11 downto 0);

-- Senales adder
signal PC_out : STD_LOGIC_VECTOR(11 downto 0);
signal adder12_out : STD_LOGIC_VECTOR(15 downto 0);
signal dummySignal : std_logic;

-- Más Senales  
signal selRAM_datain : std_logic;
signal selPC : std_logic;
signal selRAM_address : STD_LOGIC_VECTOR (1 downto 0);
signal MuxPCOut : std_logic_vector(11 downto 0);




begin

inst_RegA: Reg port map(
           clock   => clock,                        -- Se?al del clock (reducido).
           clear   => clear,                        -- Se?al de reset.
           load    => enableA,                        -- Se?al de carga.
           datain  => alu_result,   -- Se?ales de entrada de datos.
           dataout => regA_result
           );

inst_RegB: Reg port map(
           clock   => clock,                        -- Se?al del clock (reducido).
           clear   => clear,                        -- Se?al de reset.
           load    => enableB,                        -- Se?al de carga.
           datain  => alu_result,   -- Se?ales de entrada de datos.
           dataout => regB_result
           );

inst_PC: PC port map(
           clock   => clock,                        -- Se?al del clock (reducido).
           clear   => clear,                        -- Se?al de reset.
           load    => loadPC,                        -- Se?al de carga.
           datain  => MuxPCOut,   -- Se?ales de entrada de datos.
           dataout => PC_out
           );

--MUX A
with selA select
       muxA_result <= regA_result        when "00", --A
                      "0000000000000000" when "01", --ZERO
                      "0000000000000001" when "10", --ONE
                      "0000000000000000" when others; 

--MUX B
with selB select
       muxB_result <= regB_result               when "00", --B
                      "0000000000000000"        when "01", --ZERO
                      rom_dataout(35 downto 20) when "10", --LIT
                      ram_dataout               when "11"; --DOUT 
           

inst_ALU: ALU port map(
           a       => muxA_result,                  -- Primer operando.
           b       => muxB_result,                  -- Segundo operando.
           sop     => sop_signal,                   -- Selector de la operaci?n.
           c       => sigc,                     -- Se?al de 'carry'.
           z       => sigz,                     -- Se?al de 'zero'.
           n       => signn,                     -- Se?al de 'nagative'.
           result  => alu_result
);


inst_Status: Status port map(
           clock   => clock,                        -- Se?al del clock (reducido).
           clear   => clear,                        -- Se?al de reset.
           load => '1',
           c  => sigc,   -- Se?ales de entrada de datos.
           z => sigz,
           n => signn,
           dataout => from_status
);

inst_ControlUnit: ControlUnit port map(
            from_status => from_status,
            from_rom    => rom_dataout(19 downto 0),
            enableA     => enableA, --carga A
            enableB     => enableB, --carga B
            selA        => selA,
            selB        => selB,
            loadPC      => loadPC,
            selALU      => sop_signal,
            SelPC       => SelPC,
            selRAM_datain => selRAM_datain,
            selRAM_address => selRAM_address,
            decSP => decSP,
            incSP => incSP,
            w           => write
);

-- instancias e2

inst_SP: SP port map(
   clock    => clock,                        
   clear    => clear,                        
   load     => '1',                        
   incSP    => incSP,                        
   decSP    => decSP,                        
   dataout  => SP_out
   );

inst_muxS: MuxS port map(
         In1 => SP_out,
         In2 => rom_dataout(31 downto 20), 
         In3 => regB_result(11 downto 0), 
         OutMux => ram_address,
         MuxSel => selRAM_address
         );
         
inst_add: Adder12 Port map(
    a => PC_out,
    b => "000000000001",
    ci => '0',
    s => adder12_out,
    co => dummySignal
   );

inst_muxdatain: MuxDatain Port map(
         In1 => alu_result,
         In2 => adder12_out,
         OutMux => ram_datain,
         MuxSel => selRAM_datain
         );

inst_muxPC: MuxPC Port map(
         In1 => rom_dataout(31 downto 20),
         In2 => ram_dataout(11 downto 0),
         OutMux => MuxPCOut,
         MuxSel => selPC
         );

-- borramos esta linea: ram_datain <= alu_result;

-- borramos esta linea: ram_address <= rom_dataout(31 downto 20);
ram_write <= write;
dis(15 downto 8) <= regA_result(7 downto 0);
dis(7 downto 0) <= regB_result(7 downto 0);
rom_address <= PC_out;
end Behavioral;