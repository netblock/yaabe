/*
DDR1:
Please refer to JESD 79 F.

DDR2:
Please refer to JESD 79-2 F.

DDR3:
Please refer to JESD 79-3 F.

DDR4:
Please refer to JESD 79-4 D. If unavailable consider Micron 16gb_ddr4_sdram.pdf
For a pin map see union ddr4_mr_map



GDDR2:
Please refer to SDRAM 3.11.5.6 13.

GDDR3:
please refer to K4J52324QH-HJ08-Samsung-datasheet-17924974.pdf
JEDEC is SDRAM 3.11.5.7, but is outdated.

GDDR4:
Please refer to SDRAM 3.11.5.8 16.01.

GDDR5:
Please refer to JESD 212 C.01.

GDDR6:
Please refer to JESD 250 D. If unavailable consider,
2204251615_Samsung-K4Z80325BC-HC14_C2920181.pdf

GDDR7:
Please refer to JESD 239.



HBM1 and HBM2:
Please refer to JESD 235 D.

HBM3:
Please refer to JESD 238 A.
*/

#ifndef DDRMODEREGISTERS_H
#define DDRMODEREGISTERS_H
#pragma pack(push, 1) // bios data must use byte alignment

union ddr1_mr0 {
	uint16_t ddr1_mr0;
	struct { uint16_t
		burst_length    :2-0 +1, // 1=BL2, 2=BL4, 3=BL8; all else reserved
		burst_type      :3-3 +1, // 0=sequential, 1=interleave
		tCL             :6-4 +1, // 2=2,3=3, 5=1.5,6=2.5, all else reseved
		test_mode       :7-7 +1, // behaviour is vendor specific
		DLL_reset       :8-8 +1, // self clearing
		operating_rsvd :13-9 +1, // operation_mode reserved
		ID             :15-14 +1;
	};
};
union ddr1_emr1 {
	uint16_t ddr1_emr1;
	struct { uint16_t
		DLL              :0-0 +1, // 0=enable
		drive_strength   :1-1 +1, // 0=full, 1=reduced; (see SSTL_2, Class II)
		reserved         :2-2 +1, // compatibility with early DDR1
		operating_rsvd  :13-3 +1,
		ID              :15-14 +1;
	};
};



union ddr2_mr0 {
	uint16_t ddr2_mr0;
	struct { uint16_t
		burst_length  :2-0 +1, // 2=BL4, 3=BL8; all else reserved
		burst_type    :3-3 +1, // 0=sequential, 1=interleave
		tCL           :6-4 +1, // tCL=n; 0,1,7=reserved
		test_mode     :7-7 +1, // behaviour is vendor specific
		DLL_reset     :8-8 +1, // self clearing
		WR           :11-9 +1, // tWR = n+1
		PD_exit_time :12-12 +1, // 0=fast, 1=slow
		rsvd_15_13   :15-13 +1;
	};
};
union ddr2_emr1 {
	uint16_t ddr2_emr1;
	struct { uint16_t
		DLL              :0-0 +1, // 0=enable
		drive_strength   :1-1 +1, // 0=full, 1=reduced
		RTT_Nom_lo_bit   :2-2 +1, // A[6,2] -> Nom[1:0]
		Additive_Latency :5-3 +1, // 0=0...  6+=reserved
		RTT_Nom_hi_bit   :6-6 +1, // 0=disabled, 1=75 ohms, 2=150, 3=50
		OCD_calibration  :9-7 +1, // 0=exit,1=drive1,2=drive2,4=adjust,7=default
		DQS             :10-10 +1, // 0=enable
		RDQS            :11-11 +1, // 0=disable
		output_disable  :12-12 +1, // 1=turn off drivers for DQ, DQS, RDQS
		rsvd_15_13      :15-13 +1;
	};
};
union ddr2_emr2 {
	uint16_t ddr2_emr2;
	struct { uint16_t
		PASR        :2-0 +1, // 0=full (BA[2:0]=xxx), 0xx, 00x, 000, 3/4 (>1), 1xx, 11x, 111
		DCC         :3-3 +1, // 0=disable; Duty Cycle Correction
		rsvd_6_4    :6-4 +1, // reserved
		HT_SRF      :7-7 +1, // 0=disable; hi-temp self-refresh mode
		rsvd_12_8  :12-8 +1, // reserved
		rsvd_15_13 :15-13 +1;
	};
};
union ddr2_emr3 {
	uint16_t ddr2_emr3;
	struct { uint16_t
		rsvd_15_0  :15-0 +1; // all reserved
	};
};



union ddr3_mr0 {
	uint16_t ddr3_mr0;
	struct { uint16_t
		burst_length    :1-0 +1, // 0=BL8, 1=OTF 4/8, 2=BC4, 3=reserved
		CL_hi_bit       :2-2 +1, // A[2,6,5,4] -> CL[4:0]
		read_burst_type :3-3 +1, // 0=nibble sequential, 1=interleave
		CL_lo_bits      :6-4 +1, // tCL = 4+n
		testmode        :7-7 +1, // behaviour is vendor specific
		DLL_reset       :8-8 +1, // self clearing
		WR             :11-9 +1, // tWR; 16,5,6,7,8,10,12,14
		DLL_PPD        :12-12 +1, // 0=slow exit (DLL off), 1=fast (DLL on)
		RFU_15_13      :15-13 +1;
	};
};
union ddr3_mr1 {
	uint16_t ddr3_mr1;
	struct { uint16_t
		DLL              :0-0 +1, // 0=enable
		DrvStr_lo_bit    :1-1 +1, // 0=RZQ/6, 1=RZQ/7
		RTTNom_lo_bit    :2-2 +1, // A[9,6,2] -> RTT_Nom[2:0]
		Additive_Latency :4-3 +1, // 0=0, 1=tCL-1, 2=tCL-2, 3=reserved
		DrvStr_hi_bit    :5-5 +1, // A[5,1] -> DrvStr[1:0]; 2,3=reserved
		RTTNom_mid_bit   :6-6 +1, // 0=dis, RZQ/4, /2, /6, /12, /8,  6,7=rsvd
		write_leveling   :7-7 +1, // 0=disabled
		RFU_8            :8-8 +1, // reserved
		RTTNom_hi_bit    :9-9 +1, // 2,4,6 only if writelevel on and drivers on
		RFU_10          :10-10 +1, // reserved
		TDQS            :11-11 +1, // 0=disabled; Termination Data Strobe pins
		output_disable  :12-12 +1, // 1=turn off drivers for DQ, DQS, DQS#
		RFU_15_13       :15-13 +1;
	};
};
union ddr3_mr2 {
	uint16_t ddr3_mr2;
	struct { uint16_t
		PASR       :2-0 +1, // 0=full (BA[2:0]=xxx), 0xx, 00x, 000, 3/4 (>1), 1xx, 11x, 111
		CWL        :5-3 +1, // tCWl = 5+n
		ASR        :6-6 +1, // 0=manual; auto self refresh
		SRT        :7-7 +1, // 0=normal, 1=extended; self refresh temp range
		RFU_8      :8-8 +1, // reserved
		RTT_WR    :10-9 +1, // 0=off, RZQ/4, /2, reserved
		RFU_15_11 :15-11 +1;
	};
};
union ddr3_mr3 {
	uint16_t ddr3_mr3;
	struct { uint16_t
		MPR_location  :1-0 +1, // 0=predefined pattern for read sync, 1,2,3=RFU
		MPR_operation :2-2 +1, // 0=normal, 1=dataflow from MPR
		RFU_15_3     :15-3 +1;
	};
};



union ddr4_mr_map {
	uint32_t ddr4_mr_map;
	struct { uint32_t
		A0     :0-0 +1,
		A1     :1-1 +1,
		A2     :2-2 +1,
		A3     :3-3 +1,
		A4     :4-4 +1,
		A5     :5-5 +1,
		A6     :6-6 +1,
		A7     :7-7 +1,
		A8     :8-8 +1,
		A9     :9-9 +1,
		A10   :10-10 +1,
		A11   :11-11 +1,
		A12   :12-12 +1,
		A13   :13-13 +1,
		WE_n  :14-14 +1, // WE_n, CAS_n, RAS_n must be 0
		CAS_n :15-15 +1, // WE_n, CAS_n, RAS_n must be 0
		RAS_n :16-16 +1, // WE_n, CAS_n, RAS_n must be 0
		A17   :17-17 +1, // 4Gbit, 8Gbit doesn't have A17, so 0 on 16Gbit.
		BA0   :18-18 +1,
		BA1   :19-19 +1,
		BG0   :20-20 +1,
		BG1   :21-21 +1,
		_pad  :31-22 +1; // 32-bit pad
	};
	struct { uint32_t
		MR_data   :13-0 +1, // usable data bits
		MR_zero_0 :17-14 +1,
		MR_select :20-18 +1,
		MR_zero_1 :21-21 +1, // RFU, but all MR has it 0.
		_pad2     :31-22 +1; // 32-bit pad
	};
};
union ddr4_mr0 {
	uint16_t ddr4_mr0;
	struct { uint16_t
		BL          :1-0 +1, // 0=BL8; 1=OTF BC4/BC8; 2=BC4
		tCL_lo      :2-2 +1, // MR0[12,6:4,2] -> tCL[5:0]
		burst_type  :3-3 +1, // 0=nibble sequential; 1=interleave
		tCL_mid     :6-4 +1, // 0..7=9+n; 8=18 9=20 10=22 11=24 12=23 13=17 14=19 15=21 16=25 17=26 19=28 20=29 21=30 22=31 23=32
		test_mode   :7-7 +1,
		DLL_reset   :8-8 +1, // 1=reset
		tWRtRTP_lo :11-9 +1, // auto-pre; MR0[13,11:9] -> tWRtRTP[3:0]
		tCL_hi     :12-12 +1,
		tWRtRTP_hi :13-13 +1, // tWR is 2x; tRTP: 0..5=5+n; 6=12 7=11 8=13 9=14
		mr_zero    :16-14 +1;
	};
};
union ddr4_mr1 {
	uint16_t ddr4_mr1;
	struct { uint16_t
		DLL        :0-0 +1, // 1=enabled
		ODI        :2-1 +1, // drive strength; 0=RZQ/7; 1=/5; (2: micron: /6)
		AL         :4-3 +1, // additive latency; 0=0;  1=CL-1; 2=CL-2
		RXCTLE_lo  :6-5 +1, // MR1[13,6:5] -> RX_CTLE_CTRL[2:0]
		WL         :7-7 +1, // write leveling; 0=disabled; 1=enabled
		RTT_NOM   :10-8 +1, // 0=off; 1=RZQ/4 2=/2 3=/6 4=/1 5=/5 6=/3 7=/7
		TDQS      :11-11 +1, // DQS termination (x8 only); 0=disabled; 1=enabled
		Qoff      :12-12 +1, // output buffer disabled; 0=normal; 1=ODI/RTT off
		RXCTLE_hi :13-13 +1, // MR1[13,6:5] -> RX_CTLE_CTRL[2:0]
		mr_zero   :16-14 +1;
	};
};
union ddr4_mr2 {
	uint16_t ddr4_mr2;
	struct { uint16_t
		RFU_2_0  :2-0 +1,
		tCWL     :5-3 +1, // 1t preamble: 0=9 1=10 2=11 3=12 4=14 5=16 6=18 7=20; 2t pramble: 14..20
		LPASR    :7-6 +1, // auto refresh; 0=normal 1=reduced 1=extended 3=auto
		RFU_8    :8-8 +1,
		RTT_WR  :11-9 +1, // 0=disabled 1=RZQ/2 2=/1 3=HiZ 4=/3
		WRCRC   :12-12 +1, // write CRC; 0=disabled
		RFU_13  :13-13 +1,
		mr_zero :16-14 +1;
	};
};
union ddr4_mr3 {
	uint16_t ddr4_mr3;
	struct { uint16_t
		MPR_page    :1-0 +1, // multi-purpose register; 0=0..3=3
		MPR_access  :2-2 +1, // 0=normal; 1=data from MPR
		GDM         :3-3 +1, // 0=normal; 1=geared
		PDA         :4-4 +1, // per-dram addressability; 0=normal; 1=enable
		temp_sensor :5-5 +1, // 0=disabled
		FGR         :8-6 +1, // 0=1x 1=2x 3=4x; 5=OTF 1x/2x; 6=OTF 1x/4x
		tWCL       :10-9 +1, // when CRC, DM are both enabled; 0..2=4+n
		MPR_format :12-11 +1, // read format; 0=serial 1=parallell 2=staggered
		RFU_13     :13-13 +1,
		mr_zero    :16-14 +1;
	};
};
union ddr4_mr4 {
	uint16_t ddr4_mr4;
	struct { uint16_t
		MBIST_PPR            :0-0 +1, // self-contained PPR; 0=disabled
		max_power_savings    :1-1 +1, // lossy powersave; 0=normal; 1=enabled
		TCR_range            :2-2 +1, // 0=normal; 1=extended
		TCR                  :3-3 +1, // temp controlled refresh; 0=disabled
		internal_vref        :4-4 +1, // for Vrefdq training; 0=disabled
		soft_PPR             :5-5 +1, // soft post-package-repair; 0=disabled
		command_address_lat  :8-6 +1, // power savings;  0=0 1=3 2=4 3=5 4=6 5=8
		refresh_abort_mode   :9-9 +1, // 0=disabled
		read_preamble_train :10-10 +1, // o=disabled
		read_preamble       :11-11 +1, // 0=1tCK 1=2tCK
		write_preamble      :12-12 +1, // 0=1tCK; 1=2tCK, tCWL must be >9
		hard_PPR            :13-13 +1, // hard post-package-repair; 0=disabled
		mr_zero             :16-14 +1;
	};
};
union ddr4_mr5 {
	uint16_t ddr4_mr5;
	struct { uint16_t
		CA_parity       :2-0 +1, // 0=off; n-clocks: 1=4 2=5 3=6
		CRC_error       :3-3 +1, // 0=clear; 1=error
		CA_parity_error :4-4 +1, // 0=clear; 1=error
		ODT_powerdown   :5-5 +1, // 0=buffer enabled; 1=disabled
		RTT_Park        :8-6 +1, // 0=disabled 1=RZQ/4 2=/2 3=/6 4=/1 5=/5 6=/3 7=/7
		CA_parity_stop  :9-9 +1, // CA parity stops on error; 0=stop 1=continue
		data_maask     :10-10 +1, // write data mask (x8/x16 only); 0=disabled
		read_DBI       :11-11 +1, // data bus inversion; 0=disabled
		write_DBI      :12-12 +1, // data bus inversion; 0=disabled
		RFU_13         :13-13 +1,
		mr_zero        :16-14 +1;
	};
};
union ddr4_mr6 {
	uint16_t ddr4_mr6;
	struct { uint16_t
		vref_cal_val   :5-0 +1, // 0..50 = (n/154 + range) x Vddq
		vref_cal_range :6-6 +1, // 0=0.6 (range 1); 1=0.45 (range 2)
		vref_cal       :7-7 +1, // internal Vrefdq gen; 0=disable; 1=enable
		RFU_9_8        :9-8 +1,
		data_rate     :12-10 +1, // 0:<=1333; 1:<=1866; 2:<=2400; 3:<=2666; 4:<=3200
		RFU_13        :13-13 +1,
		mr_zero       :16-14 +1;
	};
};



union gddr2_mr0 {
	uint16_t gddr2_mr0;
	struct { uint16_t
		burst_length :0-0 +1, // 0=4, 1=reserved
		WL           :3-0 +1, // 1=1..7=7; 0=reserved
		RL           :6-4 +1, // 8,9,10,rsvd,4,5,6,7
		testmode     :7-7 +1, // behaviour is vendor specific
		DLL_reset    :8-8 +1, // self clearing
		WR          :11-9 +1, // tWR=n+1; 0,1,7=reserved
		rsvd_15_12  :15-12 +1;
	};
};
union gddr2_emr1 {
	uint16_t gddr2_emr1;
	struct { uint16_t
		addrcmd_ODT      :1-0 +1, // 0=off 1=1xDQ, 2=2x, 3=4xDQ
		data_ck_ODT      :3-2 +1, // 0=off, 1=auto cal., 2=60ohms, 3=120
		additive_latency :4-4 +1, // 0=0, 1=1
		DQS              :5-5 +1, // 0=differential, 1=single
		DLL              :6-6 +1, // 0=off, 1=on
		driver_Ron       :9-7 +1, // 0=60, 1=55 ... 7=25
		rankness        :10-10 +1, // 0=single 1=multi
		vendor_id       :11-11 +1, // 0=disabled 1=enabled
		rsvd_15_12      :15-12 +1;
	};
};
union gddr2_emr2 {
	uint16_t gddr2_emr2;
	struct { uint16_t
		rsvd_1_0         :1-0 +1,
		ODT_at_powerdown :2-2 +1, // 0=all off except CK, CKE, 1=EMRS/EMRS2
		low_power_mode   :3-3 +1, // 0=self-refresh, 1=fast wakeup
		CK_ODT           :5-4 +1, // 0=off, 1=1xDQ, 2=2x, 3=4xDQ
		CS_ODT           :7-6 +1, // 0=off, 1=0.5x addrcmd, 2=1x, 3=reserved
		CKE_ODT          :8-8 +1, // 0=off, 1=addrcmd
		ODT_W_mode       :9-9 +1, // 0=enable 1=disable. "W" mode??
		rsvd_11_10      :11-10 +1,
		rsvd_15_12      :15-12 +1;
	};
};
union gddr3_mr0 {
	uint16_t gddr3_mr0;
	struct { uint16_t
		burst_length :1-0 +1, // 0,1=RFU, 2=BL4, 3=BL8
		CL_hi_bit    :2-2 +1, // A[2,6,5,4]->tCL[3:0] | JEDEC says A[3] is for BL; BL[2:0]
		burst_type   :3-3 +1, // 0=sequential 1=RFU
		CL_lo_bits   :6-4 +1, // 8,9,10,11,rsvd,5,6,7,12,13,14,15, rsvd...
		test_mode    :7-7 +1, // behaviour is vendor specific
		DLL_reset    :8-8 +1, // self clearing
		tWL         :11-9 +1, // 0=reserved; tCWL
		rsvd_15_12  :15-12 +1;
	};
};
union gddr3_emr1 {
	uint16_t gddr3_emr1;
	struct { uint16_t
		drive_strength  :1-0 +1, // 0=auto cal. 1=30ohms, 2=40, 3=50
		data_terminaton :3-2 +1, // 0=ALL ODT disabled, 1=rsvd, 2=ZQ/4, 3=ZQ/2
		WR_lo_bits      :5-4 +1, // A[7,5,4] -> WR[2:0]; 11,13,5,6,7,8,9,10
		DLL             :6-6 +1, // 0=enable
		rsvd_8_8        :8-8 +1, // reserved
		R_on            :8-8 +1, // 0=40 ohms, 1=60 ohms; pull-up
		vendor_ID      :10-10 +1, // 0=off
		AddrCmd_term   :11-11 +1, // 0=inherit CKE, 1=CKE/2
		rsvd_15_12     :15-12 +1;
	};
};



union gddr4_mr0 {
	uint16_t gddr4_mr0;
	struct { uint16_t
		WR        :2-0 +1, // Write recovery; 16,18,20, 6,8,10,12,14
		tCL       :6-3 +1, // 16,17..21,22, 7,8,9..15
		testmode  :7-7 +1, // behaviour is vendor specific
		DLL_reset :8-8 +1, // self clearing
		WL       :11-9 +1, // write latency; 0=RFU, 1=1..7=7
		RFU_12   :12-12 +1, // reserved
		ID       :15-13 +1; // MR 0
	};
};
union gddr4_emr1 {
	uint16_t gddr4_emr1;
	struct { uint16_t
		Drive_Term :1-0 +1, // 0=auto cal., 2=nominal (no compensation), 1,3=RFU. (drive: 40 down/60 up ; termination: 60/120; CA 60/120/240)
		DQ_term    :3-2 +1, // 0=all off, 1=DQ off, 2=1/4, 3=1/2
		tPreamble  :6-4 +1, // 0=1..  5..7=RFU. read/write preamble in tCK
		DLL        :7-7 +1, // 0=enable
		read_DBI   :8-8 +1, // 0=disable. data bus iversion
		write_DBI  :9-9 +1, // 0=disable
		DBI_mode  :10-10 +1, // 0=DC, 1=AC. optimise for DC/AC power reduction
		Vendor_ID :11-11 +1, // 0=disable
		RFU_12    :12-12 +1, // reserved
		ID        :15-13 +1; // EMR 1
	};
};
union gddr4_emr2 {
	uint16_t gddr4_emr2;
	struct { uint16_t
		OCD_down_offset :2-0 +1, // Two's Compl. Driver/term pulldown offset
		OCD_up_offset   :5-3 +1, // Two's Compl. Driver/terminator pullup offset
		tRAS           :11-6 +1, // tRAS latency; 0=RFU, 1=1..63=63
		RFU_12         :12-12 +1, // reserved
		ID             :15-13 +1; // EMR 2
	};
};
union gddr4_emr3 {
	uint16_t gddr4_emr3;
	struct { uint16_t
		RFU           :4-0 +1, // reserved
		LP_term       :5-5 +1, // 0=disabled
		DRAM_info     :7-6 +1, // 0=vendor ID, 1=PERR_Info, 2,3=vendor specific
		parity_reset  :8-8 +1, // 0=store, 1=reset; clear PERR_Info
		parity_enable :9-9 +1, // 0=disable
		parity_mask  :11-10 +1, // 0=DQ[7:0], 1=[15:8], 2=[23:16], 3=[31:24]
		RFU_12       :12-12 +1, // reserved
		ID           :15-13 +1; // EMR 3
	};
};


union gddr5_mr0 {
	uint16_t gddr5_mr0;
	struct { uint16_t
		WLmrs       :2-0 +1, // 0=RFU 1=1..7=7
		CLmrs_lo    :6-3 +1, // tCL = 5+n. [MR8[0], MR0[6:3]] -> tCL[4:0]
		testmode    :7-7 +1, // behavior is vendor specific
		WR         :11-8 +1, // tWR = 4+n. [MR8[1], MR0[11:8]] -> tWR[4:0]
		rsvd_15_12 :15-12 +1;
	};
};
union gddr5_mr1 {
	uint16_t gddr5_mr1;
	struct { uint16_t
		drive_strength     :1-0 +1, // 0=auto cal., 1,3=vendor, 2=nom (60/40)
		data_termination   :3-2 +1, // 0=disabled, 1=ZQ, 2=ZQ/2, 3=RFU
		addrcmd_term       :5-4 +1, // 0=inherit CKE_n, 1=ZQ, 2=ZQ/2, 3=disabled
		calibration_update :6-6 +1, // 0=on; impedance calibration engine
		PLL_DLL            :7-7 +1, // 0=off
		read_DBI           :8-8 +1, // 0=on; data bus inversion
		write_DBI          :9-9 +1, // 0=on; data bus inversion
		address_BI        :10-10 +1, // 0=on; address bus inversion
		PLLDLL_reset      :11-11 +1, // self clearing
		rsvd_15_12        :15-12 +1;
	};
};
union gddr5_mr2 {
	uint16_t gddr5_mr2;
	struct { uint16_t
		drive_pulldown_offset :2-0 +1, // Two's Compl. vendor specific
		drive_pullup_offset   :5-3 +1, // Two's Compl. vendor specific
		data_wck_term_offset  :8-6 +1, // Two's Compl. vendor specific
		AddrCmd_term_offset  :11-9 +1, // Two's Compl. vendor specific
		rsvd_15_12           :15-12 +1;
	};
};
union gddr5_mr3 {
	uint16_t gddr5_mr3;
	struct { uint16_t
		self_refresh    :1-0 +1, // 0=32ms 1,2=vendor, 3=temp controlled
		WCK01_invert    :2-2 +1, // phase invert
		WCK23_invert    :3-3 +1, // phase invert
		WCK2CK_training :4-4 +1, // 0=off; WCK to CK alignment training
		RDQS_mode       :5-5 +1, // 0=off; EDC becomes RDQS
		DRAM_info       :7-6 +1, // 0=off, 1=vendor ID, 2=temp, 3=vemdor spec.
		WCK_termination :9-8 +1, // 0=dis, 1=ZQ/2, 2=ZQ, 3=RFU
		bank_groups    :11-10 +1, // 0,1=off, 2=on tCCDL=4, 3=on tCCL=3
		rsvd_15_12     :15-12 +1;
	};
};
union gddr5_mr4 {
	uint16_t gddr5_mr4;
	struct { uint16_t
		EDC_pattern  :3-0 +1, // little-endian-based burst position
		CRCWL        :6-4 +1, // 7+n; CRC write latency
		CRCRL        :8-8 +1, // 4,1,2,3; CRC read laency
		read_CRC     :9-9 +1, // 0=on
		write_crc   :10-10 +1, // 0=on
		hold_invert :11-11 +1, // 1=inverted; EDC hold pattern inversion
		rsvd_15_12  :15-12 +1;
	};
};
union gddr5_mr5 {
	uint16_t gddr5_mr5;
	struct { uint16_t
		LP1         :0-0 +1, // 0=off; power saving, relaxed core
		LP2         :1-1 +1, // 0=off; power saving, WCK off during powerdown
		LP3         :2-2 +1, // 0=off; training during refresh disabled
		PLLDLL_BW   :5-3 +1, // vendor specific; PLL bandwidth
		tRAS       :11-6 +1, // 0=RFU, 1=1..63=63
		rsvd_15_12 :15-12 +1;
	};
};
union gddr5_mr6 {
	uint16_t gddr5_mr6;
	struct { uint16_t
		WCK2CK_alignment :0-0 +1, // 0=inside DRAM, 1=at balls
		VREFD_merge      :1-1 +1, // 0=off 1=average VREFD and internal vref
		VREFD_training   :2-2 +1, // 0=ff 1=train; self clearing
		VREFD_source     :3-3 +1, // 0=VREFD pins, 1=internally generated
		VREFD_offset_MU  :7-4 +1, // semi Two's Compl. -8 = 0/auto
		VREFD_offset_AF :11-8 +1, // semi Two's Compl. -8 = 0/auto
		rsvd_15_12      :15-12 +1;
	};
};
union gddr5_mr7 {
	uint16_t gddr5_mr7;
	struct { uint16_t
		PLL_standby     :0-0 +1, // 0=off 1=standby when self-refresh
		PLL_fast_lock   :1-1 +1, // 1=faster lock but higher power; self clears
		PLL_delay_comp  :2-2 +1, // 1=PLL feedback = WCK clock tree delay
		low_freq_mode   :3-3 +1, // 1=reduced power for low freq
		WCK2CK_autosync :4-4 +1, // 1=auto WCK2CK after PD exit
		DQ_preamble     :5-5 +1, // 1=non-gapped READs will have 4UI preamble
		temp_sensor     :6-6 +1, // 1=enable temperature sense
		half_VREFD      :7-7 +1, // 0=0.7x 1=0.5x VDDQ
		VDD_range       :9-8 +1, // 0=1.5V 1,2,3=vendor; adapt to different VDD
		DCC            :11-10 +1, // 0=off, 1=start, 2=reset, 3=RFU; Duty Cycle Correction
		rsvd_15_12     :15-12 +1;
	};
};
union gddr5_mr8 {
	uint16_t gddr5_mr8;
	struct { uint16_t
		CL_EHF      :0-0 +1, // tCL range extension; see MR0
		WR_EHF      :1-1 +1, // tWR range extension; see MR0
		EDC_HiZ     :2-2 +1, // 1=Hi-Z state; precedence over all other states
		REFPB       :3-3 +1, // 1=per-bank refresh feature enable
		rsvd_11_4  :11-4 +1, // reserved
		rsvd_15_12 :15-12 +1;
	};
};
union gddr5_mr9 {
	uint16_t gddr5_mr9;
	struct { uint16_t
		vendor_specific :11-0 +1, // vendor specific features.
		rsvd_15_12      :15-12 +1;
	};
};
union gddr5_mr10 {
	uint16_t gddr5_mr10;
	struct { uint16_t
		vendor_specific :11-0 +1, // vendor specific features.
		rsvd_15_12      :15-12 +1;
	};
};
union gddr5_mr11 {
	uint16_t gddr5_mr11;
	struct { uint16_t
		PASR_banks_01   :0-0 +1, // exclude banks 0, 1
		PASR_banks_23   :1-1 +1, // exclude banks 2, 3
		PASR_banks_45   :2-2 +1, // exclude banks 4, 5
		PASR_banks_67   :3-3 +1, // exclude banks 6, 7
		PASR_banks_89   :4-4 +1, // exclude banks 8, 9
		PASR_banks_1011 :5-5 +1, // exclude banks 10, 11
		PASR_banks_1213 :6-6 +1, // exclude banks 12, 13
		PASR_banks_1415 :7-7 +1, // exclude banks 14, 15
		PASR_row_00     :8-8 +1, // exclude row segment A[13:12]=00 (MSB)
		PASR_row_01     :9-9 +1, // exclude row segment A[13:12]=01 (MSB)
		PASR_row_10    :10-10 +1, // exclude row segment A[13:12]=10 (MSB)
		PASR_row_11    :11-11 +1, // exclude row segment A[13:12]=11 (MSB)
		rsvd_15_12     :15-12 +1;
	};
	struct { uint16_t
		PASR_bank_mask         :7-0 +1, // bank exclusion mask
		PASR_row_segment_mask :11-8 +1, // row exclusion mask
		rsvd_15_12__2         :15-12 +1;
	};
};
union gddr5_mr12 {
	uint16_t gddr5_mr12;
	struct { uint16_t
		vendor_specific :11-0 +1, // vendor specific features.
		rsvd_15_12      :15-12 +1;
	};
};
union gddr5_mr13 {
	uint16_t gddr5_mr13;
	struct { uint16_t
		vendor_specific :11-0 +1, // vendor specific features.
		rsvd_15_12      :15-12 +1;
	};
};
union gddr5_mr14 {
	uint16_t gddr5_mr14;
	struct { uint16_t
		vendor_specific :11-0 +1, // vendor specific features.
		rsvd_15_12      :15-12 +1;
	};
};
union gddr5_mr15 {
	uint16_t gddr5_mr15;
	struct { uint16_t
		rsvd_7_0          :7-0 +1,
		MRE_0_disable     :8-8 +1, // 1=disable MRS commands on channel 0
		MRE_1_disable     :9-9 +1, // 1=disable MRS commands on channel 1
		address_training :10-10 +1, // 1=address training mode
		RFU              :11-11 +1, // reserved
		rsvd_15_12       :15-12 +1;
	};
};



union gddr6_mr0 {
	uint16_t gddr6_mr0; // raw data
	struct { uint16_t
		WLmrs    :2-0 +1, // tCWL, 8,9,10,11,12,5,6,7.
		RLmrs_lo :6-3 +1, // tCL = 5+n. [MR12[3], MR8[8], MR0[6:3]] -> tCL[5:0]
		testmode :7-7 +1, // Test mode; behavior is vendor specific
		WRmrs   :11-8 +1, // tWR for auto-pre, 0=4,1=5..47=51. See MR8, MR12
		ID      :15-12 +1; // MR 0
	};
};
union gddr6_mr1 {
	uint16_t gddr6_mr1; // raw data
	struct { uint16_t
		drive_stren   :1-0 +1, // 0=Auto Cal.(60/40), 1=AC(48/40). 2,3 vndr spec
		data_term     :3-2 +1, // 0=disabled 1=60ohm 2=120ohm 3=48ohm
		PLLDLL_range  :5-4 +1, // min-to-max WCK freq, vendor specific
		Cal_Upd       :6-6 +1, // Auto Calibration Engine, 0=enabled.
		PLL_DLL       :7-7 +1, // 0=disabled 1=enabled
		read_DBI      :8-8 +1, // Data Bus Inversion, for reads.   0=enabled
		write_DBI     :9-9 +1, // Data Bus Inversion, for writes.  1=disabled
		addrcmd_BI   :10-10 +1, // Command-address bus inversion.  0=enabled
		PLLDLL_reset :11-11 +1, // 1 = reset. self-clears after reset.
		ID           :15-12 +1; // MR 1
	};
};
union gddr6_mr2 {
	uint16_t gddr6_mr2; // raw data
	struct { uint16_t
		OCD_up       :2-0 +1, // output driver pullup offset. 0=0, Two's Compl.
		OCD_down     :5-3 +1, // pulldown. See JES250D Figure 33.
		self_refresh :7-6 +1, // 0=32ms, 1-2 vendor specific, 3=temp controlled
		EDC_mode     :8-8 +1, // 0=full data rate, 1=half
		RDQS         :9-9 +1, // 1 = EDC pins will act as RDQS; no CRC.
		CADT_SRF    :10-10 +1, // Self refesh while CA training
		EDC_HR      :11-11 +1, // EDC hold data rate 0=full, 1=half
		ID          :15-12 +1; // MR 2
	};
};
union gddr6_mr3 {
	uint16_t gddr6_mr3; // raw data
	struct { uint16_t
		dataWCK_term_offset :2-0 +1, // DQ, DBI & WCK termination offset. Two's.
		CA_term_offset      :5-3 +1, // command address. See MR2.
		DRAM_info           :7-6 +1, // 0=off 1=vndr ID1 2=temp 3=vndr ID2
		WR_scaling          :9-8 +1, // 1x 2x 3x value of tWR in MR8 and MR0
		bank_groups        :11-10 +1, // 0,1=off, 2=on tCCDL=4, 3=on tCCDL=3
		ID                 :15-12 +1; // MR 3
	};
};
union gddr6_mr4 {
	uint16_t gddr6_mr4; // raw data
	struct { uint16_t
		EDC_hold_pattern :3-0 +1, // little-endian. pattern during EDC idle
		CRCWL            :6-4 +1, // 15,16,RFU,10,11..21,RFU. See MR12 OP4
		CRCRL            :8-7 +1, // CRC latency for reads. 4,1,2,3.
		RDCRC            :9-9 +1, // read CRC 0=enable
		WRCRC           :10-10 +1, // write CRC 0=enable
		EDC_hold_invert :11-11 +1, // 0 = EDC hold pattern not inverted
		ID              :15-12 +1; // MR 4
	};
};
union gddr6_mr5 {
	uint16_t gddr6_mr5; // raw data
	struct { uint16_t
		LP1       :0-0 +1, // 0=off, Low Power Mode 1, relax several core params
		LP2       :1-1 +1, // WCK recievers turned off during powerdown.
		LP3       :2-2 +1, // no read/write training and temp reads during REFab
		PLLDLL_BW :5-3 +1, // PLL/DLL bandwidth. All except 0 vendor specific
		RAS      :11-6 +1, // 0,1,2...63. tRAS for auto precharge
		ID       :15-12 +1; // MR 5
	};
};
union gddr6_mr6 {
	uint16_t gddr6_mr6; // raw data
	struct { uint16_t
		VREFD_level  :6-0 +1, // 0.005x steps of VDDQ, from 0=0.49x to 95=0.965x
		pin_subaddr :11-7 +1, // pin to configure the VREFD for. See JESD250
		ID          :15-12 +1; // MR 6
	};
};
union gddr6_mr7 {
	uint16_t gddr6_mr7; // raw data
	struct { uint16_t
		WCK2CK_AP       :0-0 +1, // WCK alignment point. 0=inside 1=at balls
		hibernate       :1-1 +1, // 1=Hibernate Self Refresh mode. self clearing
		PLL_delay_comp  :2-2 +1, // 1=(PLL feedback delay == WCK clock tree)
		low_freq_mode   :3-3 +1, // 1=reduce power of input RX, clock trees
		WCK2CK_autosync :4-4 +1, // 1=auto sync, reduces WCK2CK MRS to 2.
		DQ_preamble     :5-5 +1, // 1=preamble on DQ, DBI_n for gapped reads.
		half_VREFC      :6-6 +1, // 0=0.7x VDDQ, 1=0.5x See MR6, MR9
		half_VREFD      :7-7 +1, // 0=prog'd VREFD,DFE. 1=0.5x VDDQ. See MR6,MR9
		VDD_range       :9-8 +1, // 0>1>2>3. Adapt to lower VDD voltages
		WCK_DCC        :11-10 +1, //Duty Cycle Corr. 0=off,1=start,2=RFU,3=hold
		ID             :15-12 +1; // MR 7
	};
};
union gddr6_mr8 {
	uint16_t gddr6_mr8; // raw data
	struct { uint16_t
		CA_low_term  :1-0 +1, // 0=disable, 1=60ohm, 2=120, 3=rsvd. For CA[3:0]
		CA_high_term :3-2 +1, // For CA[10:4]
		CA_TO        :4-4 +1, // Command Address Termin. Override 1=use CAL,CAH
		EDC_hiZ      :5-5 +1, // 1=Hi-Z state. Precidence over all other states.
		CK_auto_cal  :6-6 +1, // 0=auto calib. during REFab disabled, 1=enabled
		REFpb        :7-7 +1, // 0=per-bank, 1=per-2-bank
		RL_EHF       :8-8 +1, // Extends RLmrs of MR0 from 4 to 5 bits.
		WR_EHF       :9-9 +1, // Extends WRmrs of MR0 from 4 to 5 bits.
		CK_term     :11-10 +1, // 0=reset, 1=60ohm,2=120-ohm, 3=disabled
		ID          :15-12 +1; // MR 8
	};
};
union gddr6_mr9 {
	uint16_t gddr6_mr9; // raw data
	struct { uint16_t
		DFE          :3-0 +1, // 0=off, in steps of +-0.5% VDDQ or 7mV
		RFU          :6-4 +1, // reserved
		pin_subaddr :11-7 +1, // see JESD250
		ID          :15-12 +1; // MR 9
	};
};
union gddr6_mr10 {
	uint16_t gddr6_mr10; // raw data
	struct { uint16_t
		VREFC_offset  :3-0 +1, // CA bus. semi Two's Complement: -8=0
		WCK_inv_byte0 :5-4 +1, // for WCK2CK training 0=0;1=90 degr;2=180;3=270
		WCK_inv_byte1 :7-6 +1, // B1 on chan A, B0 on chan B ignored if WCK/word
		WCK2CK        :8-8 +1, // 1=enable WCK2CK alignment training
		WCK_ratio     :9-9 +1, // 0=half data rate, 1=full data rate
		WCK_term     :11-10 +1, // 0=disabled, 1=60 ohm, 2=120, 3=reserved
		ID           :15-12 +1; // MR 10
	};
};
union gddr6_mr11 {
	// 0=refresh enabled 1=refresh blocked for paticular segment or banks
	uint16_t gddr6_mr11; // raw data
	struct { uint16_t
		PASR_banks_01   :0-0 +1, // exclude banks 0, 1
		PASR_banks_23   :1-1 +1, // exclude banks 2, 3
		PASR_banks_45   :2-2 +1, // exclude banks 4, 5
		PASR_banks_67   :3-3 +1, // exclude banks 6, 7
		PASR_banks_89   :4-4 +1, // exclude banks 8, 9
		PASR_banks_1011 :5-5 +1, // exclude banks 10, 11
		PASR_banks_1213 :6-6 +1, // exclude banks 12, 13
		PASR_banks_1415 :7-7 +1, // exclude banks 14, 15
		PASR_row_00     :8-8 +1, // exclude row segment R[13:12]=00 (MSB)
		PASR_row_01     :9-9 +1, // exclude row segment R[13:12]=01 (MSB)
		PASR_row_10    :10-10 +1, // exclude row segment R[13:12]=10 (MSB)
		PASR_row_11    :11-11 +1, // exclude row segment R[13:12]=11 (MSB)
		ID             :15-12 +1; // MR 11
	};
	struct { uint16_t
		PASR_bank_mask         :7-0 +1, // bank exclusion mask
		PASR_row_segment_mask :11-8 +1, // row exclusion mask
		ID__2                 :15-12 +1; // MR 11
	};
};
union gddr6_mr12 {
	uint16_t gddr6_mr12; // raw data
	struct { uint16_t
		VDDQ_off  :0-0 +1, // 0=disabled. For Hibernate Self Refresh
		P2BR_addr :1-1 +1, // 0=LSB/BA0 1=MSB/BA3. Select "Dont Care" for REFp2b
		PRBS      :2-2 +1, // 1=Psudorandom bit stream instead of EDC hold
		RL_EHF2   :3-3 +1, // Extends RLmrs from 5 bits to 6 bits. See MR0, MR8
		CRCWL_EHF :4-4 +1, // Extends CRCWL from 3 bits to 4 bits. See MR4.
		WR_EHF2   :5-5 +1, // Extends WRmrs from 5 bits to 6 bits. See MR0, MR8
		RFU      :11-6 +1, // reserved.
		ID       :15-12 +1; // MR 12
	};
};
union gddr6_mr13 {
	uint16_t gddr6_mr13; // raw data
	struct { uint16_t
		vendor_specific :11-0 +1, // vendor specific features.
		ID              :15-12 +1; // MR 13
	};
};
union gddr6_mr14 {
	uint16_t gddr6_mr14; // raw data
	struct { uint16_t
		vendor_specific :11-0 +1, // vendor specific features.
		ID              :15-12 +1; // MR 14
	};
};
union gddr6_mr15 {
	uint16_t gddr6_mr15; // raw data
	struct { uint16_t
		MRS_to_chan_A :0-0 +1, // MRS to the two channels for individual config
		MRS_to_chan_B :1-1 +1, // 0=unblocked 1=blocked
		CA_training   :3-2 +1, // 0=off 1=rising of CK, 2=falling, 3=CABI_n,CA10
		unused       :11-4 +1, // defined to be absent
		ID           :15-12 +1; // MR 15
	};
};



union gddr7_mr0 {
	uint16_t gddr7_mr0; // raw data
	struct { uint16_t
		CABI      :0-0 +1, // CA bus inversion; 0=enable
		rsvd_2_1  :2-1 +1,
		RDCRC     :3-3 +1, // Read CRC; 0=disable
		WRCRC     :4-4 +1, // Write CRC; 0=disable
		SLX2CAT   :5-5 +1, // auto CA training after sleepmode exit; 0=enable
		SRSLX2CAT :6-6 +1, // same idea but for self-refresh sleepmode
		testmode  :7-7 +1, // Test mode; behavior is vendor specific
		PAM3      :8-8 +1, // PAM3 for DQ/DQE; 0=NRZ 1=PAM3
		severity  :9-9 +1, // ECC reporting; 0=disable
		poison   :10-10 +1, // ECC poisoning; 0=disable
		FD_flag  :11-11 +1, // postpone MR10~15 until sleep-mode entry; 0=enable
		ID_lo    :15-12 +1; // MR 0. low bits
    };
};
union gddr7_mr1 {
    uint16_t gddr7_mr1; // raw data
    struct { uint16_t
		RL      :5-0 +1, // tCL; 10=10..47=47
		RFU_7_6 :7-6 +1,
		DQERL  :11-8 +1, // additionl latency; 0=0..12=12
        ID_lo  :15-12 +1; // MR 1. low bits
    };
};
union gddr7_mr2 {
    uint16_t gddr7_mr2; // raw data
    struct { uint16_t
		WL         :4-0 +1, // tCWL; 6=6..31=31
		RFU_6_5    :6-5 +1,
		WRCRC2ERR :11-7 +1, // write error latency; 10=10..31=31
        ID_lo    :15-12 +1; // MR 2. low bits
    };
};
union gddr7_mr3 {
    uint16_t gddr7_mr3; // raw data
    struct { uint16_t
		tRAS      :6-0 +1, // 4=4..80=80
		RFU_11_7 :11-7 +1,
        ID_lo    :15-12 +1; // MR 3. low bits
    };
};
union gddr7_mr4 {
    uint16_t gddr7_mr4; // raw data
    struct { uint16_t
		WR     :6-0 +1, // write recovery for autopre; 4=4..80=80
		RFU_7  :7-7 +1,
		RTPSB :11-8 +1, // tRTP for autopre; 4=4..15=15
        ID_lo :15-12 +1; // MR 4. low bits
    };
};
union gddr7_mr5 {
    uint16_t gddr7_mr5; // raw data
    struct { uint16_t
		DQ_drvstr  :1-0 +1, // DQ/E/RCK; 0=40,1=80; 2,3=vendor
		DQ_term    :3-2 +1, // DQ/E; 0=off; 1=40,2=48,3=80
		RFU_4      :4-4 +1,
		ERR_drvstr :5-5 +1, // ERR pin; 0=40,1=80
		RFU_6      :6-6 +1,
		CAL_UPD    :8-7 +1, // 0=all; 1=dis for WCK; 2=rsvd; 3=disable all
		SEV2ERR    :9-9 +1, // error signaling; 0=disable
		DQE_HZ    :10-10 +1, // DQE in high-Z; 0=disable
		RFU_11    :11-11 +1,
        ID_lo     :15-12 +1; // MR 5. low bits
    };
};
union gddr7_mr6 {
    uint16_t gddr7_mr6; // raw data
    struct { uint16_t
		DQ_pulldown_leg1_offset :3-0 +1, // DQ/E/RCK; Two's Complement
		DQ_pulldown_leg2_offset :7-4 +1, // DQ/E/RCK; Two's Complement
		RFU_11_8               :11-8 +1,
        ID_lo                  :15-12 +1; // MR 6. low bits
    };
};
union gddr7_mr7 {
    uint16_t gddr7_mr7; // raw data
    struct { uint16_t
		DQ_pullup_leg1_offset  :3-0 +1, // DQ/E/RCK; Two's Complement
		DQ_pullup_leg2_offset  :7-4 +1, // DQ/E/RCK; Two's Complement
		DQ_termination_offset :11-8 +1, // DQ/E; Two's Complement
        ID_lo                 :15-12 +1; // MR 7. low bits
    };
};
union gddr7_mr8 {
    uint16_t gddr7_mr8; // raw data
    struct { uint16_t
		ARFM          :1-0 +1, // management level; 0=default; 1=A,2=B,3=C
		DRFM          :2-2 +1, // directed management; 0=disable
		BRC           :4-3 +1, // bounded config; 0=1,2; 1=12,3; 2=123,4; 3=rsvd
		DCC           :6-5 +1, // duty cycle; 0=disable;1=start;2=rsvd;3=hold
		self_refresh :10-9 +1, // 0=fixed; 1,2=vendor; 3=temp-controlled
		hibernate    :11-11 +1, // hibernate refresh sleep; 0=disable
        ID_lo        :15-12 +1; // MR 8. low bits
    };
};
union gddr7_mr9 {
    uint16_t gddr7_mr9; // raw data
    struct { uint16_t
		RCKMODE  :1-0 +1, // 0=disable; 1=with read; 2=with RCKSTRT; 3=always on
		RCK_LS   :2-2 +1, // pramble; 0=0,1=2 half-freq RCK cycles
		RCKEN    :7-3 +1, // enable latency; n+6; 0=6..31=37
		RFU_8    :8-8 +1,
		RCKSTOP :11-9 +1, // stop latency; n*2+10; 0=10,1=12..7=24
        ID_lo   :15-12 +1; // MR 9. low bits
    };
};
union gddr7_mr10 {
    uint16_t gddr7_mr10; // raw data
    struct { uint16_t
		RFU_11_0 :11-0 +1,
        ID_lo    :15-12 +1; // MR 10. low bits
    };
};
union gddr7_mr11 {
    uint16_t gddr7_mr11; // raw data
    struct { uint16_t
		RFU_11_0 :11-0 +1,
        ID_lo    :15-12 +1; // MR 11. low bits
    };
};
union gddr7_mr12 {
    uint16_t gddr7_mr12; // raw data
    struct { uint16_t
		VDD_range  :1-0 +1, // progressively lowers, 0>1>2>3
		VDDQ_range :3-2 +1, // progressively lowers, 0>1>2>3
		WCK_range  :8-4 +1, // 0:(Fwck<=Fwcknrz); 1..24: (n-1)/2 <=f< n/2 GHz
		RFU_9      :9-9 +1,
		RCKTYPE   :10-10 +1, // 0=single (RCK_c is HiZ), 1=differential
		RCKLEVEL  :11-11 +1, // PAM3 level; 0=full swing (+-1); 1=half (+1/0)
        ID_lo     :15-12 +1; // MR 12. low bits
    };
};
union gddr7_mr13 {
    uint16_t gddr7_mr13; // raw data
    struct { uint16_t
		CA_termination   :2-0 +1, // 0=CA1 latch; 1=48; 2=60, 3=96, 5=80, 7=off
		CA_term_offset   :5-3 +1, // Two's Complement
		WCK_termination  :8-6 +1, // 0=CA2 latch; 1=48; 2=60, 3=96, 5=80, 7=off
		WCK_term_offset :11-9 +1, // Two's Complement
        ID_lo           :15-12 +1; // MR 13. low bits
    };
};
union gddr7_mr14 {
    uint16_t gddr7_mr14; // raw data
    struct { uint16_t
		VREFCA       :6-0 +1, // 0..95: (98+n)/200 x VDDQ; default=47=.725
		DFE_CA      :10-7 +1, // DFE; 0=+-0..15=+-15 VREFCA steps
		half_VREFCA :11-11 +1, // 0=programmed; 1=0.5
        ID_lo       :15-12 +1; // MR 14. low bits
    };
};
union gddr7_mr15 {
    uint16_t gddr7_mr15; // raw data
    struct { uint16_t
		CAPAR         :0-0 +1, // CA parity; 0=disable
		CAPARBLK      :1-1 +1, // parity blocking; 0=dis; must be 0 if CAPAR==0
		CSP_FB        :2-2 +1, // CSP command feedback; 0=default
		CAPARBLK_LAT  :5-3 +1, // parity error latency; 0=0..4=4
		CAPARBLK_ctrl :6-6 +1, // 0=implicit CAPARBLK_LAT
		RFU_7         :7-7 +1,
		CAPAR2ERR    :11-8 +1, // parity error latency; 0=variable; 1=1..15=15
        ID_lo        :15-12 +1; // MR 15. low bits
    };
};
union gddr7_mr16 {
    uint16_t gddr7_mr16; // raw data
    struct { uint16_t
		VREFD_L_2 :6-0 +1, // PAM3 low; NRZ ref; (158+n)/360 * VDDQ; default=67
		RFU_7     :7-7 +1,
		L_2_addr :11-8 +1, // 0..9=DQ,10=DQE (PAM3); 12=DQ[7:0]/E (NRZ); 14=offset all; 15=all
        ID_lo    :15-12 +1; // MR 16. low bits
    };
};
union gddr7_mr17 {
    uint16_t gddr7_mr17; // raw data
    struct { uint16_t
		VREFD_H :6-0 +1, // PAM3 low; (230+n)/360 * VDDQ; default=85
		RFU_7   :7-7 +1,
		H_addr :11-8 +1, // 0..9=DQ,10=DQE (PAM3); 14=offset all; 15=all
        ID_lo  :15-12 +1; // MR 17. low bits
    };
};
union gddr7_mr18 {
    uint16_t gddr7_mr18; // raw data
    struct { uint16_t
		DQ_DQE_CTLE   :3-0 +1, // 0=off; 1=1..15=15 or max
		RFU_5_4       :5-4 +1,
		CTLE_RX_addr  :7-6 +1, // 0=both; 1=upper; 2=lower
		CTLE_IO_addr :11-8 +1, // 0..9=DQ; 10=DQE; 15=all
        ID_lo        :15-12 +1; // MR 18. low bits
    };
};
union gddr7_mr19 {
    uint16_t gddr7_mr19; // raw data
    struct { uint16_t
		DQ_DQE_DFE   :3-0 +1, // 0=off; 1=1..15=15 or max (1-tap)
		RFU_5_4      :5-4 +1,
		DFE_RX_addr  :7-6 +1, // 0=both; 1=upper; 2=lower
		DFE_IO_addr :11-8 +1, // 0..9=DQ; 10=DQE; 15=all
        ID_lo       :15-12 +1; // MR 19. low bits
    };
};
union gddr7_mr20 {
    uint16_t gddr7_mr20; // raw data
    struct { uint16_t
		scramble_code :7-0 +1, // 8-bit or 32-bit; 32UI x 8
		RFU_8         :8-8 +1,
		byte_address :11-9 +1, // 0..3=byte; 7=all
        ID_lo        :15-12 +1; // MR 20. low bits
    };
};
union gddr7_mr21 {
    uint16_t gddr7_mr21; // raw data
    struct { uint16_t
		DQ_DQE_TX_EQ :3-0 +1, // 0=off; 1=1..15=15 or max
		RFU_5_4      :7-4 +1,
		TX_EQ_addr  :11-8 +1, // 0..9=DQ; 10=DQE; 15=all
        ID_lo       :15-12 +1; // MR 21. low bits
    };
};
union gddr7_mr22 {
    uint16_t gddr7_mr22; // raw data
    struct { uint16_t
		RFU_7_0        :7-0 +1,
		ECS_LOG_RULES  :8-8 +1, // 0=maintain; 1=overwrite
		ECS_FLAG_RESET :9-9 +1, // 0=disable; 1=reset (self-clear)
		ECS_RESET     :10-10 +1, // 0=disable; 1=reset (self-clear)
		ECS_ON        :11-11 +1, // 0=disable
        ID_lo         :15-12 +1; // MR 22. low bits
    };
};
union gddr7_mr23 {
    uint16_t gddr7_mr23; // raw data
    struct { uint16_t
		DT_LFSR         :0-0 +1, // data training mode; 0=read fifo; 1=LFSR
		LFSR_TYPE       :1-1 +1, // polynomial selection; 0=PRBS15; 1=PRBS11
		LFSTR_CNT_RESET :2-2 +1, // per-lane error counter; 1=reset
		LFSTR_RST_MODE  :3-3 +1, // 0=auto after RDWTEC; 1=manual
		DT_EYE_MASK     :5-4 +1, // 0=no masking; 1=upper; 2=lower
		CAOSC           :6-6 +1, // CA bus oscillator; 0=disaable
		LFSR_CNT_MODE   :7-7 +1, // 0=12-bit combined; 1=two 6-bit
		FIFO_PTR_RST    :8-8 +1, // 1=reset
		DT_ERR_PATTERN :11-9 +1, // 0=normal 1=HiZ 2=1 3=0 4=-1 5=CK4 6=half CK4
        ID_lo          :15-12 +1; // MR 23. low bits
    };
};
union gddr7_mr24 {
    uint16_t gddr7_mr24; // raw data
    struct { uint16_t
		LFSR_seed_lo  :9-0 +1, // lower 10 of 15-bit start value; see MR25[4:0]
		LFSR_address :11-10 +1, // 0=DQ[3:0]; 1=DQ[7:4]; 2=DQ[9:8]/E
        ID_lo        :15-12 +1; // MR 24. low bits
    };
};
union gddr7_mr25 {
    uint16_t gddr7_mr25; // raw data
    struct { uint16_t
		LFSR_seed_hi  :4-0 +1, // lower 10 of 15-bit start value; see MR24[9:0]
		RFU_9_5       :9-5 +1,
		LFSR_address :11-10 +1, // 0=DQ[3:0]; 1=DQ[7:4]; 2=DQ[9:8]/E
        ID_lo        :15-12 +1; // MR 25. low bits
    };
};
union gddr7_mr26 {
    uint16_t gddr7_mr26; // raw data
    struct { uint16_t
		LFSR_SHIFT_SEL :1-0 +1, // symbol offset; n*4 symbols
		LFSR_INV       :2-2 +1, // symbol inversion; 0=not inverted
		DT_LANE_MASK   :3-3 +1, // 0 no masking
		RFU_7_4        :7-4 +1,
		IO_ADDRESS    :11-8 +1, // 0..9=DQ; 10=DQE
        ID_lo         :15-12 +1; // MR 26. low bits
    };
};
union gddr7_mr27 {
    uint16_t gddr7_mr27; // raw data
    struct { uint16_t
		err_pulldown_offset :3-0 +1, // Two's Complement
		err_pullup_offset   :7-4 +1, // Two's Complement
		RFU_11_8           :11-8 +1,
        ID_lo              :15-12 +1; // MR 27. low bits
    };
};
union gddr7_mr28 {
    uint16_t gddr7_mr28; // raw data
    struct { uint16_t
		RFU_11_0 :11-0 +1,
        ID_lo    :15-12 +1; // MR 28. low bits
    };
};
union gddr7_mr29 {
    uint16_t gddr7_mr29; // raw data
    struct { uint16_t
		DQ_map_mode :4-0 +1, //logical-to-physical; 0=disabled 16..25=DQ
		RFU_11_5   :11-5 +1,
        ID_lo      :15-12 +1; // MR 29. low bits
    };
};
union gddr7_mr30 {
    uint16_t gddr7_mr30; // raw data
    struct { uint16_t
		ECC_TM       :0-0 +1, // ECC test mode; 0=disable
		ECC_VEC      :1-1 +1, // ecc test vector; 0=codeword 0; 1=codeword 1
		ECC_PAR_SEL  :5-2 +1, // inject on parity bit 0=0..15=15
		ECC_PAR_EN   :6-6 +1, // 0=error injection disable
		ECC_PAR_RSVD :7-7 +1, // ECC_PAR_SEL is technically[7:2]
		ECC_2CH      :8-8 +1, // ECC in 2ch mode; 0=first pass; 1=second
		RFU_11_9    :11-9 +1,
        ID_lo       :15-12 +1; // MR 30. low bits
    };
};
union gddr7_mr31 {
    uint16_t gddr7_mr31; // raw data
    struct { uint16_t
		PPR_guard_key :7-0 +1, // Post Package Repair; 0xCF; 0x73; 0xBB; 0x3B
		RFU_10_8     :10-8 +1,
		hPPR        :11-11 +1, // hard PPR; 0=disable
        ID_lo       :15-12 +1; // MR 31. low bits
    };
};
union gddr7_mr32 {
    uint16_t gddr7_mr32; // raw data
    struct { uint16_t
		RFU   :11-0 +1, // MR32~47 is RFU. MR48~63 is vendor-specific
        ID_lo :15-12 +1; // MR 32~63. low bits
    };
};



// HBM2 uses HBM1
union hbm_mr0 {
	uint8_t hbm_mr0;
	struct { uint8_t
		read_DBI       :0-0 +1, // 1=enable; data bus inversion, AC.
		write_DBI      :1-1 +1, // 1=enable; data bus inversion, AC.
		TCSR           :2-2 +1, // 1=enable; temperature-controlled self-refresh
		rsvd_3_3       :3-3 +1, // reserved
		read_parity    :4-4 +1, // 0=disable; DQ parity
		write_parity   :5-5 +1, // 0=disable; DQ parity
		addrcmd_parity :6-6 +1, // 0=disable; command-address parity
		test_mode      :7-7 +1; // 1=Test mode; behavior is vendor specific
	};
};
union hbm_mr1 {
	uint8_t hbm_mr1;
	struct { uint8_t
		tWR       :4-0 +1, // 3=3,4=4...31=31. 0..2=reserved
		nom_drive :7-5 +1; // 6mA,9,12,15,18, 5..7=reserved
	};
};
union hbm_mr2 {
	uint8_t hbm_mr2;
	struct { uint8_t
		WL :2-0 +1, // [MR4[4], MR2[2:0]] -> WL[3:0]; tWL=1+n
		RL :7-3 +1; // [MR4[5], MR2[7:3]] -> RL[5:0]; tRL=2+n
	};
};
union hbm_mr3 {
	uint8_t hbm_mr3;
	struct { uint8_t
		tRAS         :5-0 +1, // 3=3... 63=63; 0,1,2=reserved
		bank_groups  :6-6 +1, // 1=enable
		burst_length :7-7 +1; // 0=BL2, 1=BL4
	};
};
union hbm_mr4 {
	uint8_t hbm_mr4;
	struct { uint8_t
		ECC      :0-0 +1, // 0=disabled; ECC and WDM are mutually exlusive.
		WDM      :1-1 +1, // 0=enabled; write data mask
		PL       :3-2 +1, // 0=0..3=3; parity latency
		EWL      :4-4 +1, // extended write latency; see MR0
		ERL      :5-5 +1, // extended read latency; see MR0
		reserved :7-6 +1; // reserved
	};
};
union hbm_mr5 {
	uint8_t hbm_mr5;
	struct { uint8_t
		TRR_bank_address :3-0 +1, // 0=0; target bank of target row
		reserved         :5-4 +1, // reserved
		TRR_peudochannel :6-6 +1, // 0=PC0, 1=PC1
		TRR_mode         :7-7 +1; // 0=disable; Target Row Refresh for rowhammer
	};
};
union hbm_mr6 {
	uint8_t hbm_mr6;
	struct { uint8_t
		reserved    :2-0 +1,
		implicit_RP :7-3 +1; // tRP=n+2; imPRE has PRE implied with ACT.
	};
};
union hbm_mr7 {
	uint8_t hbm_mr7;
	struct { uint8_t
		DWORD_loopback :0-0 +1, // 0=disable; 1=link test (MISR) mode
		DWORD_read_mux :2-1 +1, // 1=MISR regs, 2=Rx path, 3=LFSR sticky
		DWORD_MISR     :5-3 +1, // 0=preset 0xAAAAA/0x00000, 1=LFSR read, 2=register (R/W), 3=MISR write, 4=LFSR write
		reserved       :6-6 +1, // reserved
		CATTRIP        :7-7 +1; // 0=clear pin, 1=assert to 1.
	};
};
union hbm_mr8 {
	uint8_t hbm_mr8;
	struct { uint8_t
		DA28_lockout :0-0 +1, // 1=if on chan A or E, hardlock DA port
		reserved :7-1 +1; // reserved
	};
};
union hbm_mr9 {
	uint8_t hbm_mr9;
	struct { uint8_t
		reserved :7-0 +1; // reserved
	};
};
union hbm_mr10 {
	uint8_t hbm_mr10;
	struct { uint8_t
		reserved :7-0 +1; // reserved
	};
};
union hbm_mr11 {
	uint8_t hbm_mr11;
	struct { uint8_t
		reserved :7-0 +1; // reserved
	};
};
union hbm_mr12 {
	uint8_t hbm_mr12;
	struct { uint8_t
		reserved :7-0 +1; // reserved
	};
};
union hbm_mr13 {
	uint8_t hbm_mr13;
	struct { uint8_t
		reserved :7-0 +1; // reserved
	};
};
union hbm_mr14 {
	uint8_t hbm_mr14;
	struct { uint8_t
		reserved :7-0 +1; // reserved
	};
};
union hbm_mr15 {
	uint8_t hbm_mr15;
	struct { uint8_t
		internal_vref :2-0 +1, // Two's: 0.50 - 0.04*n; 0=.50, 1=.46, 4=.54
		reserved :7-3 +1; // reserved
	};
};
// HBM2 uses HBM1



union hbm3_mr0 {
	uint8_t hbm3_mr0;
	struct { uint8_t
		read_DBI       :0-0 +1, // 1=enable; data bus inversion, AC.
		write_DBI      :1-1 +1, // 1=enable; data bus inversion, AC.
		TCSR           :2-2 +1, // 1=enable; temperature-controlled self-refresh
		rsvd_3_3       :3-3 +1, // reserved
		read_parity    :4-4 +1, // 0=disable; DQ parity
		write_parity   :5-5 +1, // 0=disable; DQ parity
		addrcmd_parity :6-6 +1, // 0=disable; command-address parity
		test_mode      :7-7 +1; // 1=Test mode; behavior is vendor specific
	};
};
union hbm3_mr1 {
	uint8_t hbm3_mr1;
	struct { uint8_t
		tWL :4-0 +1, // 4=4..16=16,  0..3,17+ reserved
		tPL :7-5 +1; // 0=0..4=4, 5+ reserved
	};
};
union hbm3_mr2 {
	uint8_t hbm3_mr2;
	struct { uint8_t
		tRL :7-0 +1; // 4=4..63=63,  0..3,64+ reserved
	};
};
union hbm3_mr3 {
	uint8_t hbm3_mr3;
	struct { uint8_t
		tWR :7-0 +1; // 4=4..63=63,  0..3,64+ reserved
	};
};
union hbm3_mr4 {
	uint8_t hbm3_mr4;
	struct { uint8_t
		tRAS :7-0 +1; // 4=4..63=63,  0..3,64+ reserved
	};
};
union hbm3_mr5 {
	uint8_t hbm3_mr5;
	struct { uint8_t
		tRTP :7-0 +1; // 2=2..15=15,  0,1 reserved
	};
};
union hbm3_mr6 {
	uint8_t hbm3_mr6;
	struct { uint8_t
		drive_down_strength :2-0 +1, // 0=8mA, 1=10, *2=12, 3=14, 4+ reserved
		drive_up_strength   :5-3 +1, // 0=8mA, 1=10, *2=12, 3=14, 4+ reserved
		reserved            :7-6 +1; // reserved
	};
};
union hbm3_mr7 {
	uint8_t hbm3_mr7;
	struct { uint8_t
		DWORD_loopback :0-0 +1, // 0=disable; 1=link test (MISR) mode
		DWORD_read_mux :1-1 +1, // 0=MISR regs, 3=LFSR sticky
		reserved_2_2   :2-2 +1, // reserved
		DWORD_MISR     :5-3 +1, // 0=preset, 1=LFSR read, 2=register (R/W), 3=MISR write, 4=LFSR write
		reserved_6_6   :6-6 +1, // reserved
		CATTRIP        :7-7 +1; // 0=auto, 1=assert to 1.
	};
};
union hbm3_mr8 {
	uint8_t hbm3_mr8;
	struct { uint8_t
		DA_lockout         :0-0 +1, // 1=if on chan A or E, hardlock DA port
		duty_cycle_monitor :1-1 +1, // 0=disabled
		ECS_log_auto_clear :2-2 +1, // 0=disabled
		WDQS2CK_training   :3-3 +1, // 0=disabled
		RFM_levels         :5-4 +1, // 0=default, 1=A,2=B,3=C (1+ RFM required)
		reserved           :7-6 +1; // reserved
	};
};
union hbm3_mr9 {
	uint8_t hbm3_mr9;
	struct { uint8_t
		metadata           :0-0 +1, // 1=read/writes have metadata
		severity_reporting :1-1 +1, // 1=repoting
		ECC_testmode       :2-2 +1, // 0=disable ECC engine test mode
		ECC_test_pattern   :3-3 +1, // 0=CW0 (1's are errors), 1=CW1 (0=error)
		ECS_via_REFab      :4-4 +1, // 0=disabled
		ECS_during_SRF     :5-5 +1, // 0=disabled
		ECS_multibit       :6-6 +1, // 0=correction of multibit errors disabled
		ECS_logging        :7-7 +1; // 0=maintain, 1=reset
	};
};
union hbm3_mr10 {
	uint8_t hbm3_mr10;
	struct { uint8_t
		vendor_specific :7-0 +1;
	};
};
union hbm3_mr11 {
	uint8_t hbm3_mr11;
	struct { uint8_t
		DCA_WDQS0 :3-0 +1, // broken Two's: 0=0, 7=-7, 8=reserved, 9=+1 15=+7
		DCA_WDQS1 :7-4 +1; // broken Two's: 0=0, 7=-7, 8=reserved, 9=+1 15=+7
	};
};
union hbm3_mr12 {
	uint8_t hbm3_mr12;
	struct { uint8_t
		vendor_specific :7-0 +1;
	};
};
union hbm3_mr13 {
	uint8_t hbm3_mr13;
	struct { uint8_t
		reserved :7-0 +1; // reserved
	};
};
union hbm3_mr14 {
	uint8_t hbm3_mr14;
	struct { uint8_t
		reserved_0_0 :0-0 +1, // reserved
		VrefCA       :6-1 +1, // 0.18 + 0.01*n; 1=0.19, 63=.81. (32=.50)
		reserved_7_7 :7-7 +1; // reserved
	};
};
union hbm3_mr15 {
	uint8_t hbm3_mr15;
	struct { uint8_t
		reserved_0_0 :0-0 +1, // reserved
		VrefD        :6-1 +1, // 0.18 + 0.01*n; 1=0.19, 63=.81. (32=.50)
		reserved_7_7 :7-7 +1; // reserved
	};
};



#pragma pack(pop) // restore old packing

#endif
