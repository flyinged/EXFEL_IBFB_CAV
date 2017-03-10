------------------------------------------------------------------------------
--                       Paul Scherrer Institute (PSI)
------------------------------------------------------------------------------
-- Unit    : frame_tb.vhd
-- Author  : Goran Marinkovic, Section Diagnostic
-- Version : $Revision: 1.1 $
------------------------------------------------------------------------------
-- Copyright© PSI, Section Diagnostic
------------------------------------------------------------------------------
-- Comment : This is the top for the calculation pipeline.
------------------------------------------------------------------------------
-- Std. library (platform) ---------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- Work library (platform) ---------------------------------------------------
-- synopsys translate_off
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
-- synopsys translate_on

-- Work library (application) ------------------------------------------------
library psi_gtx_link_v1_00_a;
use psi_gtx_link_v1_00_a.virtex5_gtx_package.all;


entity frame_tb is
end frame_tb;

architecture testbench of frame_tb is

   ---------------------------------------------------------------------------
   -- System
   ---------------------------------------------------------------------------
   constant HIGH                  : std_logic := '1';
   constant LOW                   : std_logic := '0';
   constant c_clk_cycle           : time:= 8 ns;
   signal   clk                   : std_logic := '0';
   signal   rst                   : std_logic := '1';
   ---------------------------------------------------------------------------
   -- Frame interface
   ---------------------------------------------------------------------------
   signal   tx_train_trig         : std_logic := '0';
   signal   tx_train_number       : std_logic_vector(31 downto  0) := X"BEAF0000";
   signal   tx_q_new              : std_logic := '0';
   signal   tx_q                  : std_logic_vector(31 downto  0) := X"0000CACE";
   signal   tx_x_new              : std_logic := '0';
   signal   tx_x                  : std_logic_vector(31 downto  0) := X"FACE0000";
   signal   tx_y_new              : std_logic := '0';
   signal   tx_y                  : std_logic_vector(31 downto  0) := X"00001234";

   signal   rx_new                : std_logic := '0';
   signal   rx_data_0             : std_logic_vector(31 downto  0) := X"00000000";
   signal   rx_data_1             : std_logic_vector(31 downto  0) := X"00000000";
   signal   rx_data_2             : std_logic_vector(31 downto  0) := X"00000000";
   signal   rx_data_3             : std_logic_vector(31 downto  0) := X"00000000";

   signal   rx_valid_cnt          : std_logic_vector(31 downto  0) := X"00000000";
   signal   rx_error_cnt          : std_logic_vector(31 downto  0) := X"00000000";
   ---------------------------------------------------------------------------
   -- MGT Interface
   ---------------------------------------------------------------------------
   signal   tx_en                 : std_logic := '0';
   signal   tx_full               : std_logic := '0';
   signal   tx_charisk            : std_logic_vector( 3 downto  0) := X"0";
   signal   tx_data               : std_logic_vector(31 downto  0) := X"00000000";

   signal   rx_empty              : std_logic := '0';
   signal   rx_en                 : std_logic := '0';
   signal   rx_charisk            : std_logic_vector( 3 downto  0) := X"0";
   signal   rx_data               : std_logic_vector(31 downto  0) := X"00000000";

begin

   ---------------------------------------------------------------------------
   -- DUT
   ---------------------------------------------------------------------------
   frame_inst: frame
   port map
   (
      ------------------------------------------------------------------------
      -- Debug interface
      ------------------------------------------------------------------------
      debug_clk                   => open,
      debug                       => open,
      ------------------------------------------------------------------------
      -- CPU Interface
      ------------------------------------------------------------------------
      i_tx_rst                    => rst,
      i_tx_clk                    => clk,

      i_tx_train_trig             => tx_train_trig,
      i_tx_train_number           => tx_train_number,

      i_tx_q_new                  => tx_q_new,
      i_tx_q_valid                => HIGH,
      i_tx_q                      => tx_q,

      i_tx_x_new                  => tx_x_new,
      i_tx_x_valid                => HIGH,
      i_tx_x                      => tx_x,

      i_tx_y_new                  => tx_y_new,
      i_tx_y_valid                => HIGH,
      i_tx_y                      => tx_y,

      i_rx_rst                    => rst,
      i_rx_clk                    => clk,
      o_rx_new                    => rx_new,
      o_rx_data_0                 => rx_data_0,
      o_rx_data_1                 => rx_data_1,
      o_rx_data_2                 => rx_data_2,
      o_rx_data_3                 => rx_data_3,

      i_rx_valid_clr              => LOW,
      o_rx_valid_cnt              => rx_valid_cnt,
      i_rx_error_clr              => LOW,
      o_rx_error_cnt              => rx_error_cnt,
      ------------------------------------------------------------------------
      -- MGT Interface
      ------------------------------------------------------------------------
      i_tx_full                   => tx_full,
      o_tx_en                     => tx_en,
      o_tx_charisk                => tx_charisk,
      o_tx_data                   => tx_data,

      i_rx_empty                  => rx_empty,
      o_rx_en                     => rx_en,
      i_rx_charisk                => rx_charisk,
      i_rx_data                   => rx_data
   );

   ---------------------------------------------------------------------------
   -- This controls the clock
   ---------------------------------------------------------------------------
   clk_proc: process
   begin
      loop
         clk                      <= '0';
         wait for c_clk_cycle / 2;
         clk                      <= '1';
         wait for c_clk_cycle / 2;
      end loop;
   end process clk_proc;

   ---------------------------------------------------------------------------
   -- Fifo interface
   ---------------------------------------------------------------------------
   fifo36_inst: FIFO36
   generic map
   (
      DATA_WIDTH                  => 36,
      ALMOST_FULL_OFFSET          => X"080",
      ALMOST_EMPTY_OFFSET         => X"080",
      DO_REG                      => 1,
      EN_SYN                      => FALSE,
      FIRST_WORD_FALL_THROUGH     => TRUE
   )
   port map
   (
      RST                         => rst,

      WRCLK                       => clk,
      FULL                        => tx_full,
      ALMOSTFULL                  => open,
      WREN                        => tx_en,
      WRCOUNT                     => open,
      WRERR                       => open,
      DIP                         => tx_charisk,
      DI                          => tx_data,

      RDCLK                       => clk,
      EMPTY                       => rx_empty,
      ALMOSTEMPTY                 => open,
      RDEN                        => rx_en,
      RDCOUNT                     => open,
      RDERR                       => open,
      DOP                         => rx_charisk,
      DO                          => rx_data
   );

   ---------------------------------------------------------------------------
   -- Stimulus
   ---------------------------------------------------------------------------
   stimuli_proc: process
   begin
      ------------------------------------------------------------------------
      -- Initial values
      ------------------------------------------------------------------------
      rst                         <= '1';
      wait for 10 * c_clk_cycle;
      rst                         <= '0';
      wait for 10 * c_clk_cycle;
      tx_q_new                    <= '1';
      tx_x_new                    <= '1';
      tx_y_new                    <= '1';
      wait for 1 * c_clk_cycle;
      tx_q_new                    <= '0';
      tx_x_new                    <= '0';
      tx_y_new                    <= '0';
      ------------------------------------------------------------------------
      -- Done
      ------------------------------------------------------------------------
      wait;
   end process stimuli_proc;

end testbench;

------------------------------------------------------------------------------
-- End of file
------------------------------------------------------------------------------
