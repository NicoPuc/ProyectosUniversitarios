----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 24.07.2023 18:44:16
-- Design Name: 
-- Module Name: D_Latch - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity D_Latch is
    Port ( D : in STD_LOGIC;
           C : in STD_LOGIC;
           Q : out STD_LOGIC);
end D_Latch;

architecture Behavioral of D_Latch is

component RS_Latch
      Port (
          R : in STD_LOGIC;
          S : in STD_LOGIC;
          Q : out STD_LOGIC
      );
end component;


signal first_nand : STD_LOGIC;
signal second_nand : STD_LOGIC;


begin

first_nand <= D nand C;
second_nand <= (not D) nand C;

inst_RS: RS_Latch port map(

    R=>first_nand,
    S =>second_nand,
    Q =>Q
);


end Behavioral;
