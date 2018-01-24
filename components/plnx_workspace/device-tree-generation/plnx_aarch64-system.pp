# 1 "/home/ykiveish/workspace/petabuilds/xilinx-zcu102-2017.2/build/../components/plnx_workspace/device-tree-generation/system-top.dts"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/home/ykiveish/workspace/petabuilds/xilinx-zcu102-2017.2/build/../components/plnx_workspace/device-tree-generation/system-top.dts"







/dts-v1/;
/include/ "zynqmp.dtsi"
/include/ "zynqmp-clk-ccf.dtsi"
/include/ "zcu102-revb.dtsi"
/include/ "pl.dtsi"
/include/ "pcw.dtsi"
/ {
 chosen {
  bootargs = "earlycon clk_ignore_unused";
  stdout-path = "serial0:115200n8";
 };
 aliases {
  ethernet0 = &gem3;
  serial0 = &uart0;
  serial1 = &uart1;
  spi0 = &qspi;
 };
 memory {
  device_type = "memory";
  reg = <0x0 0x0 0x0 0x80000000>, <0x00000008 0x00000000 0x0 0x80000000>;
 };
 cpus {
 };
};
# 1 "/home/ykiveish/workspace/petabuilds/xilinx-zcu102-2017.2/build/tmp/work/plnx_aarch64-xilinx-linux/device-tree-generation/xilinx+gitAUTOINC+43551819a1-r0/system-user.dtsi" 1
/include/ "system-conf.dtsi"
/ {
};
# 32 "/home/ykiveish/workspace/petabuilds/xilinx-zcu102-2017.2/build/../components/plnx_workspace/device-tree-generation/system-top.dts" 2
