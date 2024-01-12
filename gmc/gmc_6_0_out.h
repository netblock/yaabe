
union atc_ats_cntl {
	uint32_t atc_ats_cntl;
	struct { uint32_t
		disable_atc     :0-0 +1,
		disable_pri     :1-1 +1,
		disable_pasid   :2-2 +1,
		rsvd0           :7-3 +1,
		credits_ats_rpb :13-8 +1,
		rsvd1           :15-14 +1,
		debug_eco       :19-16 +1,
		rsvd2           :31-20 +1;
	};
};

union atc_ats_debug {
	uint32_t atc_ats_debug;
	struct { uint32_t
		invalidate_all                                        :0-0 +1,
		ident_return                                          :1-1 +1,
		address_translation_request_write_perms               :2-2 +1,
		rsvd0                                                 :4-3 +1,
		page_requests_use_relaxed_ordering                    :5-5 +1,
		priv_bit                                              :6-6 +1,
		exe_bit                                               :7-7 +1,
		page_request_perms                                    :8-8 +1,
		untranslated_only_requests_carry_size                 :9-9 +1,
		num_requests_at_err                                   :13-10 +1,
		disallow_err_to_done                                  :14-14 +1,
		ignore_fed                                            :15-15 +1,
		invalidation_requests_disallowed_when_atc_is_disabled :16-16 +1,
		rsvd1                                                 :31-17 +1;
	};
};

union atc_ats_default_page_cntl {
	uint32_t atc_ats_default_page_cntl;
	struct { uint32_t
		send_default_page :0-0 +1,
		rsvd0             :1-1 +1,
		default_page_high :5-2 +1,
		rsvd1             :31-6 +1;
	};
};

union atc_ats_default_page_low {
	uint32_t atc_ats_default_page_low;
	struct { uint32_t
		default_page :31-0 +1;
	};
};

union atc_ats_fault_cntl {
	uint32_t atc_ats_fault_cntl;
	struct { uint32_t
		fault_register_log    :5-0 +1,
		rsvd0                 :9-6 +1,
		fault_interrupt_table :15-10 +1,
		rsvd1                 :19-16 +1,
		fault_crash_table     :25-20 +1,
		rsvd2                 :31-26 +1;
	};
};

union atc_ats_fault_debug {
	uint32_t atc_ats_fault_debug;
	struct { uint32_t
		credits_ats_ih                             :4-0 +1,
		rsvd0                                      :7-5 +1,
		allow_subsequent_fault_status_addr_updates :8-8 +1,
		rsvd1                                      :15-9 +1,
		clear_fault_status_addr                    :16-16 +1,
		rsvd2                                      :31-17 +1;
	};
};

union atc_ats_fault_status_addr {
	uint32_t atc_ats_fault_status_addr;
	struct { uint32_t
		page_addr :31-0 +1;
	};
};

union atc_ats_fault_status_info {
	uint32_t atc_ats_fault_status_info;
	struct { uint32_t
		fault_type     :5-0 +1,
		rsvd0          :9-6 +1,
		vmid           :14-10 +1,
		extra_info     :15-15 +1,
		extra_info2    :16-16 +1,
		invalidation   :17-17 +1,
		page_request   :18-18 +1,
		status         :23-19 +1,
		page_addr_high :27-24 +1,
		rsvd1          :31-28 +1;
	};
};

union atc_ats_status {
	uint32_t atc_ats_status;
	struct { uint32_t
		busy               :0-0 +1,
		crashed            :1-1 +1,
		deadlock_detection :2-2 +1,
		rsvd0              :31-3 +1;
	};
};

union atc_l1_address_offset {
	uint32_t atc_l1_address_offset;
	struct { uint32_t
		logical_address :31-0 +1;
	};
};

union atc_l1_cntl {
	uint32_t atc_l1_cntl;
	struct { uint32_t
		dont_need_ats_behavior :1-0 +1,
		need_ats_behavior      :2-2 +1,
		rsvd0                  :3-3 +1,
		need_ats_snoop_default :4-4 +1,
		rsvd1                  :31-5 +1;
	};
};

union atc_l1rd_debug_tlb {
	uint32_t atc_l1rd_debug_tlb;
	struct { uint32_t
		disable_fragments         :0-0 +1,
		rsvd0                     :3-1 +1,
		effective_cam_size        :7-4 +1,
		effective_work_queue_size :10-8 +1,
		rsvd1                     :11-11 +1,
		credits_l1_l2             :17-12 +1,
		rsvd2                     :19-18 +1,
		credits_l1_rpb            :27-20 +1,
		debug_eco                 :29-28 +1,
		invalidate_all            :30-30 +1,
		rsvd3                     :31-31 +1;
	};
};

union atc_l1rd_status {
	uint32_t atc_l1rd_status;
	struct { uint32_t
		busy               :0-0 +1,
		deadlock_detection :1-1 +1,
		rsvd0              :7-2 +1,
		bad_need_ats       :8-8 +1,
		rsvd1              :31-9 +1;
	};
};

union atc_l1wr_debug_tlb {
	uint32_t atc_l1wr_debug_tlb;
	struct { uint32_t
		disable_fragments         :0-0 +1,
		rsvd0                     :3-1 +1,
		effective_cam_size        :7-4 +1,
		effective_work_queue_size :10-8 +1,
		rsvd1                     :11-11 +1,
		credits_l1_l2             :17-12 +1,
		rsvd2                     :19-18 +1,
		credits_l1_rpb            :27-20 +1,
		debug_eco                 :29-28 +1,
		invalidate_all            :30-30 +1,
		rsvd3                     :31-31 +1;
	};
};

union atc_l1wr_status {
	uint32_t atc_l1wr_status;
	struct { uint32_t
		busy               :0-0 +1,
		deadlock_detection :1-1 +1,
		rsvd0              :7-2 +1,
		bad_need_ats       :8-8 +1,
		rsvd1              :31-9 +1;
	};
};

union atc_l2_cntl {
	uint32_t atc_l2_cntl;
	struct { uint32_t
		number_of_translation_read_requests              :1-0 +1,
		rsvd0                                            :3-2 +1,
		number_of_translation_write_requests             :5-4 +1,
		rsvd1                                            :9-6 +1,
		number_of_translation_reads_depends_on_addr_mod  :10-10 +1,
		number_of_translation_writes_depends_on_addr_mod :11-11 +1,
		rsvd2                                            :31-12 +1;
	};
};

union atc_l2_debug {
	uint32_t atc_l2_debug;
	struct { uint32_t
		credits_l2_ats :5-0 +1,
		rsvd0          :31-6 +1;
	};
};

union atc_misc_cg {
	uint32_t atc_misc_cg;
	struct { uint32_t
		offdly        :11-6 +1,
		rsvd0         :17-12 +1,
		enable        :18-18 +1,
		mem_ls_enable :19-19 +1,
		rsvd1         :31-20 +1;
	};
};

union atc_vm_aperture0_cntl2 {
	uint32_t atc_vm_aperture0_cntl2;
	struct { uint32_t
		vmids_using_range :15-0 +1,
		rsvd0             :31-16 +1;
	};
};

union atc_vm_aperture0_cntl {
	uint32_t atc_vm_aperture0_cntl;
	struct { uint32_t
		ats_access_mode :1-0 +1,
		rsvd0           :31-2 +1;
	};
};

union atc_vm_aperture0_high_addr {
	uint32_t atc_vm_aperture0_high_addr;
	struct { uint32_t
		virtual_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union atc_vm_aperture0_low_addr {
	uint32_t atc_vm_aperture0_low_addr;
	struct { uint32_t
		virtual_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union atc_vm_aperture1_cntl2 {
	uint32_t atc_vm_aperture1_cntl2;
	struct { uint32_t
		vmids_using_range :15-0 +1,
		rsvd0             :31-16 +1;
	};
};

union atc_vm_aperture1_cntl {
	uint32_t atc_vm_aperture1_cntl;
	struct { uint32_t
		ats_access_mode :1-0 +1,
		rsvd0           :31-2 +1;
	};
};

union atc_vm_aperture1_high_addr {
	uint32_t atc_vm_aperture1_high_addr;
	struct { uint32_t
		virtual_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union atc_vm_aperture1_low_addr {
	uint32_t atc_vm_aperture1_low_addr;
	struct { uint32_t
		virtual_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union atc_vmid0_pasid_mapping {
	uint32_t atc_vmid0_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid10_pasid_mapping {
	uint32_t atc_vmid10_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid11_pasid_mapping {
	uint32_t atc_vmid11_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid12_pasid_mapping {
	uint32_t atc_vmid12_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid13_pasid_mapping {
	uint32_t atc_vmid13_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid14_pasid_mapping {
	uint32_t atc_vmid14_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid15_pasid_mapping {
	uint32_t atc_vmid15_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid1_pasid_mapping {
	uint32_t atc_vmid1_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid2_pasid_mapping {
	uint32_t atc_vmid2_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid3_pasid_mapping {
	uint32_t atc_vmid3_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid4_pasid_mapping {
	uint32_t atc_vmid4_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid5_pasid_mapping {
	uint32_t atc_vmid5_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid6_pasid_mapping {
	uint32_t atc_vmid6_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid7_pasid_mapping {
	uint32_t atc_vmid7_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid8_pasid_mapping {
	uint32_t atc_vmid8_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid9_pasid_mapping {
	uint32_t atc_vmid9_pasid_mapping;
	struct { uint32_t
		pasid  :15-0 +1,
		rsvd0  :30-16 +1,
		valid  :31-31 +1;
	};
};

union atc_vmid_pasid_mapping_update_status {
	uint32_t atc_vmid_pasid_mapping_update_status;
	struct { uint32_t
		vmid0_remapping_finished  :0-0 +1,
		vmid1_remapping_finished  :1-1 +1,
		vmid2_remapping_finished  :2-2 +1,
		vmid3_remapping_finished  :3-3 +1,
		vmid4_remapping_finished  :4-4 +1,
		vmid5_remapping_finished  :5-5 +1,
		vmid6_remapping_finished  :6-6 +1,
		vmid7_remapping_finished  :7-7 +1,
		vmid8_remapping_finished  :8-8 +1,
		vmid9_remapping_finished  :9-9 +1,
		vmid10_remapping_finished :10-10 +1,
		vmid11_remapping_finished :11-11 +1,
		vmid12_remapping_finished :12-12 +1,
		vmid13_remapping_finished :13-13 +1,
		vmid14_remapping_finished :14-14 +1,
		vmid15_remapping_finished :15-15 +1,
		rsvd0                     :31-16 +1;
	};
};

union cc_mc_max_channel {
	uint32_t cc_mc_max_channel;
	struct { uint32_t
		noofchan :4-1 +1,
		rsvd0    :31-5 +1;
	};
};

union dll_cntl {
	uint32_t dll_cntl;
	struct { uint32_t
		dll_reset_time :9-0 +1,
		rsvd0          :11-10 +1,
		dll_lock_time  :21-12 +1,
		rsvd1          :23-22 +1,
		mrdck0_bypass  :24-24 +1,
		mrdck1_bypass  :25-25 +1,
		pwr2_mode      :26-26 +1,
		rsvd2          :31-27 +1;
	};
};

union gmcon_debug {
	uint32_t gmcon_debug;
	struct { uint32_t
		gfx_stall  :0-0 +1,
		gfx_clear  :1-1 +1,
		misc_flags :29-2 +1,
		rsvd0      :31-30 +1;
	};
};

union gmcon_misc2 {
	uint32_t gmcon_misc2;
	struct { uint32_t
		reng_mem_power_ctrl_override0 :2-0 +1,
		reng_mem_power_ctrl_override1 :5-3 +1,
		rsvd0                         :9-6 +1,
		reng_sr_hold_threshold        :15-10 +1,
		stctrl_lpt_target             :27-16 +1,
		stctrl_ignore_arb_busy        :28-28 +1,
		stctrl_extend_gmc_offline     :29-29 +1,
		rsvd1                         :31-30 +1;
	};
};

union gmcon_misc3 {
	uint32_t gmcon_misc3;
	struct { uint32_t
		reng_disable_mcc            :5-0 +1,
		reng_disable_mcd            :11-6 +1,
		stctrl_force_pgfsm_cmd_done :23-12 +1,
		rsvd0                       :31-24 +1;
	};
};

union gmcon_misc {
	uint32_t gmcon_misc;
	struct { uint32_t
		reng_execute_now_mode          :10-10 +1,
		reng_execute_on_reg_update     :11-11 +1,
		reng_srbm_credits_mcd          :15-12 +1,
		stctrl_stutter_en              :16-16 +1,
		stctrl_gmc_idle_threshold      :18-17 +1,
		stctrl_srbm_idle_threshold     :20-19 +1,
		stctrl_ignore_pre_sr           :21-21 +1,
		stctrl_ignore_allow_stop       :22-22 +1,
		stctrl_ignore_sr_commit        :23-23 +1,
		stctrl_ignore_protection_fault :24-24 +1,
		stctrl_disable_allow_sr        :25-25 +1,
		stctrl_disable_gmc_offline     :26-26 +1,
		critical_regs_lock             :27-27 +1,
		allow_deep_sleep_mode          :29-28 +1,
		stctrl_force_allow_sr          :30-30 +1,
		rsvd0                          :31-31 +1;
	};
};

union gmcon_perf_mon_cntl0 {
	uint32_t gmcon_perf_mon_cntl0;
	struct { uint32_t
		start_thresh :11-0 +1,
		stop_thresh  :23-12 +1,
		start_mode   :25-24 +1,
		stop_mode    :27-26 +1,
		allow_wrap   :28-28 +1,
		rsvd0        :31-29 +1;
	};
};

union gmcon_perf_mon_cntl1 {
	uint32_t gmcon_perf_mon_cntl1;
	struct { uint32_t
		thresh_cntr_id :5-0 +1,
		start_trig_id  :11-6 +1,
		stop_trig_id   :17-12 +1,
		mon0_id        :23-18 +1,
		mon1_id        :29-24 +1,
		rsvd0          :31-30 +1;
	};
};

union gmcon_perf_mon_rslt0 {
	uint32_t gmcon_perf_mon_rslt0;
	struct { uint32_t
		count  :31-0 +1;
	};
};

union gmcon_perf_mon_rslt1 {
	uint32_t gmcon_perf_mon_rslt1;
	struct { uint32_t
		count  :31-0 +1;
	};
};

union gmcon_pgfsm_config {
	uint32_t gmcon_pgfsm_config;
	struct { uint32_t
		fsm_addr      :7-0 +1,
		power_down    :8-8 +1,
		power_up      :9-9 +1,
		p1_select     :10-10 +1,
		p2_select     :11-11 +1,
		write         :12-12 +1,
		read          :13-13 +1,
		rsrvd         :26-14 +1,
		srbm_override :27-27 +1,
		reg_addr      :31-28 +1;
	};
};

union gmcon_pgfsm_read {
	uint32_t gmcon_pgfsm_read;
	struct { uint32_t
		read_value         :23-0 +1,
		pgfsm_select       :27-24 +1,
		serdes_master_busy :28-28 +1,
		rsvd0              :31-29 +1;
	};
};

union gmcon_pgfsm_write {
	uint32_t gmcon_pgfsm_write;
	struct { uint32_t
		write_value :31-0 +1;
	};
};

union gmcon_reng_execute {
	uint32_t gmcon_reng_execute;
	struct { uint32_t
		reng_execute_on_pwr_up     :0-0 +1,
		reng_execute_now           :1-1 +1,
		reng_execute_now_start_ptr :11-2 +1,
		reng_execute_dsp_end_ptr   :21-12 +1,
		reng_execute_end_ptr       :31-22 +1;
	};
};

union gmcon_reng_ram_data {
	uint32_t gmcon_reng_ram_data;
	struct { uint32_t
		reng_ram_data :31-0 +1;
	};
};

union gmcon_reng_ram_index {
	uint32_t gmcon_reng_ram_index;
	struct { uint32_t
		reng_ram_index :9-0 +1,
		rsvd0          :31-10 +1;
	};
};

union gmcon_stctrl_register_save_excl_set0 {
	uint32_t gmcon_stctrl_register_save_excl_set0;
	struct { uint32_t
		stctrl_register_save_excl0 :15-0 +1,
		stctrl_register_save_excl1 :31-16 +1;
	};
};

union gmcon_stctrl_register_save_excl_set1 {
	uint32_t gmcon_stctrl_register_save_excl_set1;
	struct { uint32_t
		stctrl_register_save_excl2 :15-0 +1,
		stctrl_register_save_excl3 :31-16 +1;
	};
};

union gmcon_stctrl_register_save_range0 {
	uint32_t gmcon_stctrl_register_save_range0;
	struct { uint32_t
		stctrl_register_save_base0  :15-0 +1,
		stctrl_register_save_limit0 :31-16 +1;
	};
};

union gmcon_stctrl_register_save_range1 {
	uint32_t gmcon_stctrl_register_save_range1;
	struct { uint32_t
		stctrl_register_save_base1  :15-0 +1,
		stctrl_register_save_limit1 :31-16 +1;
	};
};

union gmcon_stctrl_register_save_range2 {
	uint32_t gmcon_stctrl_register_save_range2;
	struct { uint32_t
		stctrl_register_save_base2  :15-0 +1,
		stctrl_register_save_limit2 :31-16 +1;
	};
};

union mc_arb_addr_hash {
	uint32_t mc_arb_addr_hash;
	struct { uint32_t
		bank_xor_enable :3-0 +1,
		col_xor         :11-4 +1,
		row_xor         :27-12 +1,
		rsvd0           :31-28 +1;
	};
};

union mc_arb_age_rd {
	uint32_t mc_arb_age_rd;
	struct { uint32_t
		rate_group0   :1-0 +1,
		rate_group1   :3-2 +1,
		rate_group2   :5-4 +1,
		rate_group3   :7-6 +1,
		rate_group4   :9-8 +1,
		rate_group5   :11-10 +1,
		rate_group6   :13-12 +1,
		rate_group7   :15-14 +1,
		enable_group0 :16-16 +1,
		enable_group1 :17-17 +1,
		enable_group2 :18-18 +1,
		enable_group3 :19-19 +1,
		enable_group4 :20-20 +1,
		enable_group5 :21-21 +1,
		enable_group6 :22-22 +1,
		enable_group7 :23-23 +1,
		divide_group0 :24-24 +1,
		divide_group1 :25-25 +1,
		divide_group2 :26-26 +1,
		divide_group3 :27-27 +1,
		divide_group4 :28-28 +1,
		divide_group5 :29-29 +1,
		divide_group6 :30-30 +1,
		divide_group7 :31-31 +1;
	};
};

union mc_arb_age_wr {
	uint32_t mc_arb_age_wr;
	struct { uint32_t
		rate_group0   :1-0 +1,
		rate_group1   :3-2 +1,
		rate_group2   :5-4 +1,
		rate_group3   :7-6 +1,
		rate_group4   :9-8 +1,
		rate_group5   :11-10 +1,
		rate_group6   :13-12 +1,
		rate_group7   :15-14 +1,
		enable_group0 :16-16 +1,
		enable_group1 :17-17 +1,
		enable_group2 :18-18 +1,
		enable_group3 :19-19 +1,
		enable_group4 :20-20 +1,
		enable_group5 :21-21 +1,
		enable_group6 :22-22 +1,
		enable_group7 :23-23 +1,
		divide_group0 :24-24 +1,
		divide_group1 :25-25 +1,
		divide_group2 :26-26 +1,
		divide_group3 :27-27 +1,
		divide_group4 :28-28 +1,
		divide_group5 :29-29 +1,
		divide_group6 :30-30 +1,
		divide_group7 :31-31 +1;
	};
};

union mc_arb_bankmap {
	uint32_t mc_arb_bankmap;
	struct { uint32_t
		bank0  :3-0 +1,
		bank1  :7-4 +1,
		bank2  :11-8 +1,
		bank3  :15-12 +1,
		rank   :19-16 +1,
		rsvd0  :31-20 +1;
	};
};

union mc_arb_burst_time {
	uint32_t mc_arb_burst_time;
	struct { uint32_t
		state0 :4-0 +1,
		state1 :9-5 +1,
		state2 :14-10 +1,
		state3 :19-15 +1,
		rsvd0  :31-20 +1;
	};
};

union mc_arb_cac_cntl {
	uint32_t mc_arb_cac_cntl;
	struct { uint32_t
		enable         :0-0 +1,
		read_weight    :6-1 +1,
		write_weight   :12-7 +1,
		allow_overflow :13-13 +1,
		rsvd0          :31-14 +1;
	};
};

union mc_arb_cg {
	uint32_t mc_arb_cg;
	struct { uint32_t
		cg_arb_req  :7-0 +1,
		cg_arb_resp :15-8 +1,
		rsvd0       :31-16 +1;
	};
};

union mc_arb_dram_timing_1 {
	uint32_t mc_arb_dram_timing_1;
	struct { uint32_t
		actrd     :7-0 +1,
		actwr     :15-8 +1,
		rasmactrd :23-16 +1,
		rasmactwr :31-24 +1;
	};
};

union mc_arb_dram_timing2_1 {
	uint32_t mc_arb_dram_timing2_1;
	struct { uint32_t
		ras2ras  :7-0 +1,
		rp       :15-8 +1,
		wrplusrp :23-16 +1,
		bus_turn :28-24 +1,
		rsvd0    :31-29 +1;
	};
};

union mc_arb_dram_timing2 {
	uint32_t mc_arb_dram_timing2;
	struct { uint32_t
		ras2ras  :7-0 +1,
		rp       :15-8 +1,
		wrplusrp :23-16 +1,
		bus_turn :28-24 +1,
		rsvd0    :31-29 +1;
	};
};

union mc_arb_dram_timing {
	uint32_t mc_arb_dram_timing;
	struct { uint32_t
		actrd     :7-0 +1,
		actwr     :15-8 +1,
		rasmactrd :23-16 +1,
		rasmactwr :31-24 +1;
	};
};

union mc_arb_fed_cntl {
	uint32_t mc_arb_fed_cntl;
	struct { uint32_t
		mode                :1-0 +1,
		wr_err              :3-2 +1,
		keep_poison_in_page :4-4 +1,
		rsvd0               :31-5 +1;
	};
};

union mc_arb_gdec_rd_cntl {
	uint32_t mc_arb_gdec_rd_cntl;
	struct { uint32_t
		pagebit0        :3-0 +1,
		pagebit1        :7-4 +1,
		use_rank        :8-8 +1,
		use_rsno        :9-9 +1,
		rem_default_grp :13-10 +1,
		rsvd0           :31-14 +1;
	};
};

union mc_arb_gdec_wr_cntl {
	uint32_t mc_arb_gdec_wr_cntl;
	struct { uint32_t
		pagebit0        :3-0 +1,
		pagebit1        :7-4 +1,
		use_rank        :8-8 +1,
		use_rsno        :9-9 +1,
		rem_default_grp :13-10 +1,
		rsvd0           :31-14 +1;
	};
};

union mc_arb_gecc2_cli {
	uint32_t mc_arb_gecc2_cli;
	struct { uint32_t
		no_gecc_cli0 :7-0 +1,
		no_gecc_cli1 :15-8 +1,
		no_gecc_cli2 :23-16 +1,
		no_gecc_cli3 :31-24 +1;
	};
};

union mc_arb_gecc2 {
	uint32_t mc_arb_gecc2;
	struct { uint32_t
		close_bank_rmw :14-14 +1,
		colfifo_water  :20-15 +1,
		rsvd0          :31-21 +1;
	};
};

union mc_arb_gecc2_debug2 {
	uint32_t mc_arb_gecc2_debug2;
	struct { uint32_t
		period     :7-0 +1,
		err0_start :15-8 +1,
		err1_start :23-16 +1,
		err2_start :31-24 +1;
	};
};

union mc_arb_gecc2_debug {
	uint32_t mc_arb_gecc2_debug;
	struct { uint32_t
		num_err_bits :1-0 +1,
		direction    :2-2 +1,
		data_field   :4-3 +1,
		sw_injection :5-5 +1,
		rsvd0        :31-6 +1;
	};
};

union mc_arb_gecc2 {
	uint32_t mc_arb_gecc2;
	struct { uint32_t
		enable        :0-0 +1,
		ecc_mode      :2-1 +1,
		rsvd0         :4-3 +1,
		exor_bank_sel :6-5 +1,
		rsvd1         :31-7 +1;
	};
};

union mc_arb_gecc2_misc {
	uint32_t mc_arb_gecc2_misc;
	struct { uint32_t
		streak_break :3-0 +1,
		rsvd0        :31-4 +1;
	};
};

union mc_arb_gecc2 {
	uint32_t mc_arb_gecc2;
	struct { uint32_t
		page_bit0   :4-3 +1,
		rsvd0       :6-5 +1,
		no_gecc_cli :10-7 +1,
		read_err    :13-11 +1,
		rsvd1       :31-14 +1;
	};
};

union mc_arb_gecc2_status {
	uint32_t mc_arb_gecc2_status;
	struct { uint32_t
		corr_sts0     :0-0 +1,
		uncorr_sts0   :1-1 +1,
		fed_sts0      :2-2 +1,
		rsvd0         :3-3 +1,
		corr_sts1     :4-4 +1,
		uncorr_sts1   :5-5 +1,
		fed_sts1      :6-6 +1,
		rsvd1         :7-7 +1,
		corr_clear0   :8-8 +1,
		uncorr_clear0 :9-9 +1,
		fed_clear0    :10-10 +1,
		rsvd2         :11-11 +1,
		corr_clear1   :12-12 +1,
		uncorr_clear1 :13-13 +1,
		fed_clear1    :14-14 +1,
		rsvd0         :31-15 +1;
	};
};

union mc_arb_lazy0_rd {
	uint32_t mc_arb_lazy0_rd;
	struct { uint32_t
		group0 :7-0 +1,
		group1 :15-8 +1,
		group2 :23-16 +1,
		group3 :31-24 +1;
	};
};

union mc_arb_lazy0_wr {
	uint32_t mc_arb_lazy0_wr;
	struct { uint32_t
		group0 :7-0 +1,
		group1 :15-8 +1,
		group2 :23-16 +1,
		group3 :31-24 +1;
	};
};

union mc_arb_lazy1_rd {
	uint32_t mc_arb_lazy1_rd;
	struct { uint32_t
		group4 :7-0 +1,
		group5 :15-8 +1,
		group6 :23-16 +1,
		group7 :31-24 +1;
	};
};

union mc_arb_lazy1_wr {
	uint32_t mc_arb_lazy1_wr;
	struct { uint32_t
		group4 :7-0 +1,
		group5 :15-8 +1,
		group6 :23-16 +1,
		group7 :31-24 +1;
	};
};

union mc_arb_lm_rd {
	uint32_t mc_arb_lm_rd;
	struct { uint32_t
		streak_limit        :7-0 +1,
		streak_limit_uber   :15-8 +1,
		streak_break        :16-16 +1,
		streak_uber         :17-17 +1,
		enable_two_list     :18-18 +1,
		popidle_rst_twolist :19-19 +1,
		skid1_rst_twolist   :20-20 +1,
		bankgroup_config    :23-21 +1,
		rsvd0               :31-24 +1;
	};
};

union mc_arb_lm_wr {
	uint32_t mc_arb_lm_wr;
	struct { uint32_t
		streak_limit        :7-0 +1,
		streak_limit_uber   :15-8 +1,
		streak_break        :16-16 +1,
		streak_uber         :17-17 +1,
		enable_two_list     :18-18 +1,
		popidle_rst_twolist :19-19 +1,
		skid1_rst_twolist   :20-20 +1,
		bankgroup_config    :23-21 +1,
		rsvd0               :31-24 +1;
	};
};

union mc_arb_minclks {
	uint32_t mc_arb_minclks;
	struct { uint32_t
		read_clks     :7-0 +1,
		write_clks    :15-8 +1,
		arb_rw_switch :16-16 +1,
		rsvd0         :31-17 +1;
	};
};

union mc_arb_misc2 {
	uint32_t mc_arb_misc2;
	struct { uint32_t
		tccdl4_bankbit3_xor_enable  :5-5 +1,
		tccdl4_bankbit3_xor_colbit4 :6-6 +1,
		tccdl4_bankbit3_xor_colbit5 :7-7 +1,
		tccdl4_bankbit3_xor_colbit6 :8-8 +1,
		tccdl4_bankbit3_xor_colbit7 :9-9 +1,
		tccdl4_bankbit3_xor_colbit8 :10-10 +1,
		pop_idle_replay             :11-11 +1,
		rdret_no_reordering         :12-12 +1,
		rdret_no_bp                 :13-13 +1,
		rdret_seq_skid              :17-14 +1,
		gecc                        :18-18 +1,
		gecc_rst                    :19-19 +1,
		gecc_status                 :20-20 +1,
		tagfifo_threshold           :24-21 +1,
		wcdr_replay_maskcnt         :27-25 +1,
		replay_debug                :28-28 +1,
		arb_debug29                 :29-29 +1,
		seq_rdy_pop_idle            :30-30 +1,
		tccdl4_replay_eob           :31-31 +1;
	};
};

union mc_arb_misc {
	uint32_t mc_arb_misc;
	struct { uint32_t
		sticky_rfsh      :0-0 +1,
		idle_rfsh        :1-1 +1,
		stutter_rfsh     :2-2 +1,
		chan_couple      :10-3 +1,
		harshness        :18-11 +1,
		smart_rdwr_sw    :19-19 +1,
		cali_enable      :20-20 +1,
		cali_rates       :22-21 +1,
		dispurgvld_nowrt :23-23 +1,
		dispurg_nosw2wr  :24-24 +1,
		dispurg_stall    :25-25 +1,
		dispurg_throttle :29-26 +1,
		rsvd0            :31-30 +1;
	};
};

union mc_arb_pm_cntl {
	uint32_t mc_arb_pm_cntl;
	struct { uint32_t
		override_cgstate :1-0 +1,
		ovrr_cgrfsh      :2-2 +1,
		ovrr_cgsqm       :3-3 +1,
		srfsh_on_d1      :4-4 +1,
		blkout_on_d1     :5-5 +1,
		idle_on_d1       :6-6 +1,
		ovrr_pm          :7-7 +1,
		ovrr_pm_state    :9-8 +1,
		ovrr_rd          :10-10 +1,
		ovrr_rd_state    :11-11 +1,
		ovrr_wr          :12-12 +1,
		ovrr_wr_state    :13-13 +1,
		ovrr_rfsh        :14-14 +1,
		ovrr_rfsh_state  :15-15 +1,
		rsvd0            :17-16 +1,
		idle_on_d2       :18-18 +1,
		idle_on_d3       :19-19 +1,
		idle_cnt         :23-20 +1,
		rsvd1            :31-24 +1;
	};
};

union mc_arb_pop {
	uint32_t mc_arb_pop;
	struct { uint32_t
		enable_arb               :0-0 +1,
		spec_open                :1-1 +1,
		pop_depth                :5-2 +1,
		wrdataindex_depth        :11-6 +1,
		skid_depth               :14-12 +1,
		wait_after_rfsh          :16-15 +1,
		quick_stop               :17-17 +1,
		enable_two_page          :18-18 +1,
		allow_eob_by_wrret_stall :19-19 +1,
		rsvd0                    :31-20 +1;
	};
};

union mc_arb_ramcfg {
	uint32_t mc_arb_ramcfg;
	struct { uint32_t
		noofbank   :1-0 +1,
		noofranks  :2-2 +1,
		noofrows   :5-3 +1,
		noofcols   :7-6 +1,
		chansize   :8-8 +1,
		rsvd0      :11-9 +1,
		noofgroups :12-12 +1,
		rsvd1      :31-13 +1;
	};
};

union mc_arb_remreq {
	uint32_t mc_arb_remreq;
	struct { uint32_t
		rd_water         :7-0 +1,
		wr_water         :15-8 +1,
		wr_maxburst_size :19-16 +1,
		wr_lazy_timer    :23-20 +1,
		rsvd0            :31-24 +1;
	};
};

union mc_arb_replay {
	uint32_t mc_arb_replay;
	struct { uint32_t
		enable_rd           :0-0 +1,
		enable_wr           :1-1 +1,
		wrack_mode          :2-2 +1,
		waw_enable          :3-3 +1,
		raw_enable          :4-4 +1,
		ignore_wr_cdc       :5-5 +1,
		break_on_stall      :6-6 +1,
		bos_enable_wait_cyc :7-7 +1,
		bos_wait_cyc        :14-8 +1,
		rsvd0               :31-15 +1;
	};
};

union mc_arb_ret_credits_rd {
	uint32_t mc_arb_ret_credits_rd;
	struct { uint32_t
		lcl           :7-0 +1,
		hub           :15-8 +1,
		disp          :23-16 +1,
		return_credit :31-24 +1;
	};
};

union mc_arb_ret_credits_wr {
	uint32_t mc_arb_ret_credits_wr;
	struct { uint32_t
		lcl            :7-0 +1,
		hub            :15-8 +1,
		return_credit  :23-16 +1,
		wrret_seq_skid :27-24 +1,
		rsvd0          :31-28 +1;
	};
};

union mc_arb_rfsh_cntl {
	uint32_t mc_arb_rfsh_cntl;
	struct { uint32_t
		enable :0-0 +1,
		urg0   :5-1 +1,
		urg1   :10-6 +1,
		accum  :11-11 +1,
		rsvd0  :31-12 +1;
	};
};

union mc_arb_rfsh_rate {
	uint32_t mc_arb_rfsh_rate;
	struct { uint32_t
		powermode0 :7-0 +1,
		rsvd0      :31-8 +1;
	};
};

union mc_arb_rtt_cntl0 {
	uint32_t mc_arb_rtt_cntl0;
	struct { uint32_t
		enable              :0-0 +1,
		start_idle          :1-1 +1,
		start_r2w           :3-2 +1,
		flush_on_enter      :4-4 +1,
		harsh_start         :5-5 +1,
		tps_harsh_priority  :6-6 +1,
		twrt_harsh_priority :7-7 +1,
		break_on_harsh      :8-8 +1,
		break_on_urgentrd   :9-9 +1,
		break_on_urgentwr   :10-10 +1,
		train_period        :13-11 +1,
		start_r2w_rfsh      :14-14 +1,
		debug_rsv_0         :15-15 +1,
		debug_rsv_1         :16-16 +1,
		debug_rsv_2         :17-17 +1,
		debug_rsv_3         :18-18 +1,
		debug_rsv_4         :19-19 +1,
		debug_rsv_5         :20-20 +1,
		debug_rsv_6         :21-21 +1,
		debug_rsv_7         :22-22 +1,
		debug_rsv_8         :23-23 +1,
		data_cntl           :24-24 +1,
		neighbor_bit        :25-25 +1,
		rsvd0               :31-26 +1;
	};
};

union mc_arb_rtt_cntl1 {
	uint32_t mc_arb_rtt_cntl1;
	struct { uint32_t
		window_size          :4-0 +1,
		window_update        :5-5 +1,
		window_inc_threshold :12-6 +1,
		window_dec_threshold :19-13 +1,
		window_size_max      :24-20 +1,
		window_size_min      :29-25 +1,
		window_update_count  :31-30 +1;
	};
};

union mc_arb_rtt_cntl2 {
	uint32_t mc_arb_rtt_cntl2;
	struct { uint32_t
		sample_cnt             :5-0 +1,
		phase_adjust_threshold :11-6 +1,
		phase_adjust_size      :12-12 +1,
		filter_cntl            :13-13 +1,
		rsvd0                  :31-14 +1;
	};
};

union mc_arb_rtt_data {
	uint32_t mc_arb_rtt_data;
	struct { uint32_t
		pattern :7-0 +1,
		rsvd0   :31-8 +1;
	};
};

union mc_arb_rtt_debug {
	uint32_t mc_arb_rtt_debug;
	struct { uint32_t
		debug_byte_ch0    :1-0 +1,
		debug_byte_ch1    :3-2 +1,
		shifted_phase_ch0 :11-4 +1,
		window_size_ch0   :16-12 +1,
		shifted_phase_ch1 :24-17 +1,
		window_size_ch1   :29-25 +1,
		rsvd0             :31-30 +1;
	};
};

union mc_arb_sqm_cntl {
	uint32_t mc_arb_sqm_cntl;
	struct { uint32_t
		min_penal      :7-0 +1,
		dyn_sqm_enable :8-8 +1,
		sqm_reserve    :15-9 +1,
		ratio          :23-16 +1,
		ratio_debug    :31-24 +1;
	};
};

union mc_arb_tm_cntl_rd {
	uint32_t mc_arb_tm_cntl_rd;
	struct { uint32_t
		groupby_rank :0-0 +1,
		bank_select  :2-1 +1,
		match_rank   :3-3 +1,
		match_bank   :4-4 +1,
		rsvd0        :31-5 +1;
	};
};

union mc_arb_tm_cntl_wr {
	uint32_t mc_arb_tm_cntl_wr;
	struct { uint32_t
		groupby_rank :0-0 +1,
		bank_select  :2-1 +1,
		match_rank   :3-3 +1,
		match_bank   :4-4 +1,
		rsvd0        :31-5 +1;
	};
};

union mc_arb_wcdr_2 {
	uint32_t mc_arb_wcdr_2;
	struct { uint32_t
		wpre_inc_step      :3-0 +1,
		wpre_min_threshold :8-4 +1,
		debug_0            :9-9 +1,
		debug_1            :10-10 +1,
		debug_2            :11-11 +1,
		debug_3            :12-12 +1,
		debug_4            :13-13 +1,
		debug_5            :14-14 +1,
		rsvd0              :31-15 +1;
	};
};

union mc_arb_wcdr {
	uint32_t mc_arb_wcdr;
	struct { uint32_t
		idle_enable          :0-0 +1,
		seq_idle             :1-1 +1,
		idle_period          :6-2 +1,
		idle_burst           :12-7 +1,
		idle_burst_mode      :13-13 +1,
		idle_wakeup          :15-14 +1,
		idle_deglitch_enable :16-16 +1,
		wpre_enable          :17-17 +1,
		wpre_threshold       :21-18 +1,
		wpre_max_burst       :24-22 +1,
		wpre_inc_read        :25-25 +1,
		wpre_inc_skididle    :26-26 +1,
		wpre_inc_seqidle     :27-27 +1,
		wpre_twopage         :28-28 +1,
		rsvd0                :31-29 +1;
	};
};

union mc_arb_wtm_cntl_rd {
	uint32_t mc_arb_wtm_cntl_rd;
	struct { uint32_t
		wtmode             :1-0 +1,
		harsh_pri          :2-2 +1,
		allow_stutter_grp0 :3-3 +1,
		allow_stutter_grp1 :4-4 +1,
		allow_stutter_grp2 :5-5 +1,
		allow_stutter_grp3 :6-6 +1,
		allow_stutter_grp4 :7-7 +1,
		allow_stutter_grp5 :8-8 +1,
		allow_stutter_grp6 :9-9 +1,
		allow_stutter_grp7 :10-10 +1,
		rsvd0              :31-11 +1;
	};
};

union mc_arb_wtm_cntl_wr {
	uint32_t mc_arb_wtm_cntl_wr;
	struct { uint32_t
		wtmode             :1-0 +1,
		harsh_pri          :2-2 +1,
		allow_stutter_grp0 :3-3 +1,
		allow_stutter_grp1 :4-4 +1,
		allow_stutter_grp2 :5-5 +1,
		allow_stutter_grp3 :6-6 +1,
		allow_stutter_grp4 :7-7 +1,
		allow_stutter_grp5 :8-8 +1,
		allow_stutter_grp6 :9-9 +1,
		allow_stutter_grp7 :10-10 +1,
		rsvd0              :31-11 +1;
	};
};

union mc_arb_wtm_grpwt_rd {
	uint32_t mc_arb_wtm_grpwt_rd;
	struct { uint32_t
		grp0    :1-0 +1,
		grp1    :3-2 +1,
		grp2    :5-4 +1,
		grp3    :7-6 +1,
		grp4    :9-8 +1,
		grp5    :11-10 +1,
		grp6    :13-12 +1,
		grp7    :15-14 +1,
		grp_ext :23-16 +1,
		rsvd0   :31-24 +1;
	};
};

union mc_arb_wtm_grpwt_wr {
	uint32_t mc_arb_wtm_grpwt_wr;
	struct { uint32_t
		grp0    :1-0 +1,
		grp1    :3-2 +1,
		grp2    :5-4 +1,
		grp3    :7-6 +1,
		grp4    :9-8 +1,
		grp5    :11-10 +1,
		grp6    :13-12 +1,
		grp7    :15-14 +1,
		grp_ext :23-16 +1,
		rsvd0   :31-24 +1;
	};
};

union mc_bist_auto_cntl {
	uint32_t mc_bist_auto_cntl;
	struct { uint32_t
		mop        :1-0 +1,
		rsvd0      :3-2 +1,
		adr_gen    :7-4 +1,
		lfsr_key   :23-8 +1,
		lfsr_reset :24-24 +1,
		adr_reset  :25-25 +1,
		rsvd1      :31-26 +1;
	};
};

union mc_bist_cmd_cntl {
	uint32_t mc_bist_cmd_cntl;
	struct { uint32_t
		reset              :0-0 +1,
		cmd_issue_mode     :1-1 +1,
		cmd_issue_loop     :2-2 +1,
		loop_end_condition :3-3 +1,
		loop_cnt_max       :15-4 +1,
		cmd_issue_mode_u   :16-16 +1,
		cmd_issue_run      :17-17 +1,
		loop_cnt_rd        :27-18 +1,
		enable_d0          :28-28 +1,
		enable_d1          :29-29 +1,
		status_ch          :30-30 +1,
		done               :31-31 +1;
	};
};

union mc_bist_cmp_cntl_2 {
	uint32_t mc_bist_cmp_cntl_2;
	struct { uint32_t
		data_store_cnt     :4-0 +1,
		rsvd0              :7-5 +1,
		data_store_cnt_rst :8-8 +1,
		rsvd1              :11-9 +1,
		edc_store_cnt      :16-12 +1,
		rsvd2              :19-17 +1,
		edc_store_cnt_rst  :20-20 +1,
		rsvd3              :31-21 +1;
	};
};

union mc_bist_cmp_cntl {
	uint32_t mc_bist_cmp_cntl;
	struct { uint32_t
		cmp_mask_byte   :3-0 +1,
		cmp_mask_bit    :11-4 +1,
		load_rtedc      :12-12 +1,
		data_store_sel  :13-13 +1,
		edc_store_sel   :14-14 +1,
		enable_cmd_fifo :15-15 +1,
		cmp             :17-16 +1,
		dat_mode        :18-18 +1,
		edc_store_mode  :19-19 +1,
		data_store_mode :21-20 +1,
		mismatch_cnt    :31-22 +1;
	};
};

union mc_bist_cntl {
	uint32_t mc_bist_cntl;
	struct { uint32_t
		reset          :0-0 +1,
		run            :1-1 +1,
		ptr_rst_d0     :2-2 +1,
		ptr_rst_d1     :3-3 +1,
		mop_mode       :4-4 +1,
		adr_mode       :5-5 +1,
		dat_mode       :6-6 +1,
		rsvd0          :9-7 +1,
		loop           :11-10 +1,
		enable_d0      :12-12 +1,
		enable_d1      :13-13 +1,
		load_rtdata_ch :14-14 +1,
		rsvd1          :15-15 +1,
		loop_cnt       :27-16 +1,
		rsvd2          :29-28 +1,
		done           :30-30 +1,
		load_rtdata    :31-31 +1;
	};
};

union mc_bist_data_mask {
	uint32_t mc_bist_data_mask;
	struct { uint32_t
		mask   :31-0 +1;
	};
};

union mc_bist_data_word0 {
	uint32_t mc_bist_data_word0;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_bist_data_word1 {
	uint32_t mc_bist_data_word1;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_bist_data_word2 {
	uint32_t mc_bist_data_word2;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_bist_data_word3 {
	uint32_t mc_bist_data_word3;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_bist_data_word4 {
	uint32_t mc_bist_data_word4;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_bist_data_word5 {
	uint32_t mc_bist_data_word5;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_bist_data_word6 {
	uint32_t mc_bist_data_word6;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_bist_data_word7 {
	uint32_t mc_bist_data_word7;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_bist_dir_cntl {
	uint32_t mc_bist_dir_cntl;
	struct { uint32_t
		mop        :2-0 +1,
		eob        :3-3 +1,
		mop_load   :4-4 +1,
		data_load  :5-5 +1,
		cmd_rtr_d0 :6-6 +1,
		dat_rtr_d0 :7-7 +1,
		cmd_rtr_d1 :8-8 +1,
		dat_rtr_d1 :9-9 +1,
		mop3       :10-10 +1,
		rsvd0      :31-11 +1;
	};
};

union mc_bist_eaddr {
	uint32_t mc_bist_eaddr;
	struct { uint32_t
		col    :9-0 +1,
		row    :23-10 +1,
		bank   :27-24 +1,
		rank   :28-28 +1,
		colh   :29-29 +1,
		rowh   :31-30 +1;
	};
};

union mc_bist_mismatch_addr {
	uint32_t mc_bist_mismatch_addr;
	struct { uint32_t
		col    :9-0 +1,
		row    :23-10 +1,
		bank   :27-24 +1,
		rank   :28-28 +1,
		colh   :29-29 +1,
		rowh   :31-30 +1;
	};
};

union mc_bist_rdata_edc {
	uint32_t mc_bist_rdata_edc;
	struct { uint32_t
		edc    :31-0 +1;
	};
};

union mc_bist_rdata_mask {
	uint32_t mc_bist_rdata_mask;
	struct { uint32_t
		mask   :31-0 +1;
	};
};

union mc_bist_rdata_word0 {
	uint32_t mc_bist_rdata_word0;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_bist_rdata_word1 {
	uint32_t mc_bist_rdata_word1;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_bist_rdata_word2 {
	uint32_t mc_bist_rdata_word2;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_bist_rdata_word3 {
	uint32_t mc_bist_rdata_word3;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_bist_rdata_word4 {
	uint32_t mc_bist_rdata_word4;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_bist_rdata_word5 {
	uint32_t mc_bist_rdata_word5;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_bist_rdata_word6 {
	uint32_t mc_bist_rdata_word6;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_bist_rdata_word7 {
	uint32_t mc_bist_rdata_word7;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_bist_saddr {
	uint32_t mc_bist_saddr;
	struct { uint32_t
		col    :9-0 +1,
		row    :23-10 +1,
		bank   :27-24 +1,
		rank   :28-28 +1,
		colh   :29-29 +1,
		rowh   :31-30 +1;
	};
};

union mc_cg_config {
	uint32_t mc_cg_config;
	struct { uint32_t
		index  :21-6 +1,
		rsvd0  :31-22 +1;
	};
};

union mc_cg_config_mcd {
	uint32_t mc_cg_config_mcd;
	struct { uint32_t
		mcd0_wr_enable :0-0 +1,
		mcd1_wr_enable :1-1 +1,
		mcd2_wr_enable :2-2 +1,
		mcd3_wr_enable :3-3 +1,
		mcd4_wr_enable :4-4 +1,
		mcd5_wr_enable :5-5 +1,
		rsvd0          :7-6 +1,
		mc_rd_enable   :10-8 +1,
		rsvd1          :12-11 +1,
		index          :28-13 +1,
		rsvd2          :31-29 +1;
	};
};

union mc_cg_config {
	uint32_t mc_cg_config;
	struct { uint32_t
		mcdw_wr_enable :0-0 +1,
		mcdx_wr_enable :1-1 +1,
		mcdy_wr_enable :2-2 +1,
		mcdz_wr_enable :3-3 +1,
		mc_rd_enable   :5-4 +1,
		rsvd0          :31-6 +1;
	};
};

union mc_cg_dataport {
	uint32_t mc_cg_dataport;
	struct { uint32_t
		data_field :31-0 +1;
	};
};

union mc_citf_cntl {
	uint32_t mc_citf_cntl;
	struct { uint32_t
		ignorepm             :2-2 +1,
		exemptpm             :3-3 +1,
		gfx_idle_override    :5-4 +1,
		mcd_srbm_mask_enable :6-6 +1,
		rsvd0                :31-7 +1;
	};
};

union mc_citf_credits_arb_rd {
	uint32_t mc_citf_credits_arb_rd;
	struct { uint32_t
		read_lcl :7-0 +1,
		read_hub :15-8 +1,
		read_pri :23-16 +1,
		lcl_pri  :24-24 +1,
		hub_pri  :25-25 +1,
		rsvd0    :31-26 +1;
	};
};

union mc_citf_credits_arb_wr {
	uint32_t mc_citf_credits_arb_wr;
	struct { uint32_t
		write_lcl :7-0 +1,
		write_hub :15-8 +1,
		hub_pri   :16-16 +1,
		lcl_pri   :17-17 +1,
		rsvd0     :31-18 +1;
	};
};

union mc_citf_credits_vm {
	uint32_t mc_citf_credits_vm;
	struct { uint32_t
		read_all  :5-0 +1,
		write_all :11-6 +1,
		rsvd0     :31-12 +1;
	};
};

union mc_citf_credits_xbar {
	uint32_t mc_citf_credits_xbar;
	struct { uint32_t
		read_lcl  :7-0 +1,
		write_lcl :15-8 +1,
		rsvd0     :31-16 +1;
	};
};

union mc_citf_dagb_cntl {
	uint32_t mc_citf_dagb_cntl;
	struct { uint32_t
		jump_ahead          :0-0 +1,
		center_rd_max_burst :4-1 +1,
		disable_self_init   :5-5 +1,
		center_wr_max_burst :9-6 +1,
		rsvd0               :31-10 +1;
	};
};

union mc_citf_dagb_dly {
	uint32_t mc_citf_dagb_dly;
	struct { uint32_t
		dly    :4-0 +1,
		rsvd0  :15-5 +1,
		cli    :20-16 +1,
		rsvd1  :23-21 +1,
		pos    :28-24 +1,
		rsvd2  :31-29 +1;
	};
};

union mc_citf_int_credits {
	uint32_t mc_citf_int_credits;
	struct { uint32_t
		remrdret       :5-0 +1,
		rsvd0          :11-6 +1,
		cntr_rd_hub_lp :17-12 +1,
		cntr_rd_hub_hp :23-18 +1,
		cntr_rd_lcl    :29-24 +1,
		rsvd1          :31-30 +1;
	};
};

union mc_citf_int_credits_wr {
	uint32_t mc_citf_int_credits_wr;
	struct { uint32_t
		cntr_wr_hub :5-0 +1,
		cntr_wr_lcl :11-6 +1,
		rsvd0       :31-12 +1;
	};
};

union mc_citf_misc_rd_cg {
	uint32_t mc_citf_misc_rd_cg;
	struct { uint32_t
		ondly         :5-0 +1,
		offdly        :11-6 +1,
		rdydly        :17-12 +1,
		enable        :18-18 +1,
		mem_ls_enable :19-19 +1,
		rsvd0         :31-20 +1;
	};
};

union mc_citf_misc_vm_cg {
	uint32_t mc_citf_misc_vm_cg;
	struct { uint32_t
		ondly         :5-0 +1,
		offdly        :11-6 +1,
		rdydly        :17-12 +1,
		enable        :18-18 +1,
		mem_ls_enable :19-19 +1,
		rsvd0         :31-20 +1;
	};
};

union mc_citf_misc_wr_cg {
	uint32_t mc_citf_misc_wr_cg;
	struct { uint32_t
		ondly         :5-0 +1,
		offdly        :11-6 +1,
		rdydly        :17-12 +1,
		enable        :18-18 +1,
		mem_ls_enable :19-19 +1,
		rsvd0         :31-20 +1;
	};
};

union mc_citf_perf_mon_cntl2 {
	uint32_t mc_citf_perf_mon_cntl2;
	struct { uint32_t
		cid    :8-0 +1,
		rsvd0  :31-9 +1;
	};
};

union mc_citf_perf_mon_rslt2 {
	uint32_t mc_citf_perf_mon_rslt2;
	struct { uint32_t
		cb_rd_busy  :6-6 +1,
		db_rd_busy  :7-7 +1,
		tc0_rd_busy :8-8 +1,
		vc0_rd_busy :9-9 +1,
		tc1_rd_busy :10-10 +1,
		vc1_rd_busy :11-11 +1,
		cb_wr_busy  :12-12 +1,
		db_wr_busy  :13-13 +1,
		sx_wr_busy  :14-14 +1,
		tc2_rd_busy :15-15 +1,
		tc0_wr_busy :16-16 +1,
		tc1_wr_busy :17-17 +1,
		tc2_wr_busy :18-18 +1,
		rsvd0       :31-19 +1;
	};
};

union mc_citf_remreq {
	uint32_t mc_citf_remreq;
	struct { uint32_t
		read_credits   :6-0 +1,
		write_credits  :13-7 +1,
		credits_enable :14-14 +1,
		rsvd0          :31-15 +1;
	};
};

union mc_citf_ret_mode {
	uint32_t mc_citf_ret_mode;
	struct { uint32_t
		inorder_rd :0-0 +1,
		inorder_wr :1-1 +1,
		rempri_rd  :2-2 +1,
		rempri_wr  :3-3 +1,
		lclpri_rd  :4-4 +1,
		lclpri_wr  :5-5 +1,
		rsvd0      :31-6 +1;
	};
};

union mc_citf_wtm_rd_cntl {
	uint32_t mc_citf_wtm_rd_cntl;
	struct { uint32_t
		group0_decrement :2-0 +1,
		group1_decrement :5-3 +1,
		group2_decrement :8-6 +1,
		group3_decrement :11-9 +1,
		group4_decrement :14-12 +1,
		group5_decrement :17-15 +1,
		group6_decrement :20-18 +1,
		group7_decrement :23-21 +1,
		disable_remote   :24-24 +1,
		rsvd0            :31-25 +1;
	};
};

union mc_citf_wtm_wr_cntl {
	uint32_t mc_citf_wtm_wr_cntl;
	struct { uint32_t
		group0_decrement :2-0 +1,
		group1_decrement :5-3 +1,
		group2_decrement :8-6 +1,
		group3_decrement :11-9 +1,
		group4_decrement :14-12 +1,
		group5_decrement :17-15 +1,
		group6_decrement :20-18 +1,
		group7_decrement :23-21 +1,
		disable_remote   :24-24 +1,
		rsvd0            :31-25 +1;
	};
};

union mc_citf_xtra_enable {
	uint32_t mc_citf_xtra_enable;
	struct { uint32_t
		cb1_rd  :0-0 +1,
		cb1_wr  :1-1 +1,
		db1_rd  :2-2 +1,
		db1_wr  :3-3 +1,
		tc2_rd  :4-4 +1,
		rsvd0   :7-5 +1,
		arb_dbg :11-8 +1,
		tc2_wr  :12-12 +1,
		rsvd1   :31-13 +1;
	};
};

union mc_config {
	uint32_t mc_config;
	struct { uint32_t
		mcc_index_mode_enable :31-31 +1;
	};
};

union mc_config_mcd {
	uint32_t mc_config_mcd;
	struct { uint32_t
		mcd0_wr_enable        :0-0 +1,
		mcd1_wr_enable        :1-1 +1,
		mcd2_wr_enable        :2-2 +1,
		mcd3_wr_enable        :3-3 +1,
		mcd4_wr_enable        :4-4 +1,
		mcd5_wr_enable        :5-5 +1,
		rsvd0                 :7-6 +1,
		mc_rd_enable          :10-8 +1,
		rsvd1                 :30-11 +1,
		mcd_index_mode_enable :31-31 +1;
	};
};

union mc_config {
	uint32_t mc_config;
	struct { uint32_t
		mcdw_wr_enable :0-0 +1,
		mcdx_wr_enable :1-1 +1,
		mcdy_wr_enable :2-2 +1,
		mcdz_wr_enable :3-3 +1,
		mc_rd_enable   :5-4 +1,
		rsvd0          :31-6 +1;
	};
};

union mc_hub_misc_dbg {
	uint32_t mc_hub_misc_dbg;
	struct { uint32_t
		select0 :3-0 +1,
		select1 :7-4 +1,
		rsvd0   :31-8 +1;
	};
};

union mc_hub_misc_framing {
	uint32_t mc_hub_misc_framing;
	struct { uint32_t
		bits   :31-0 +1;
	};
};

union mc_hub_misc_hub_cg {
	uint32_t mc_hub_misc_hub_cg;
	struct { uint32_t
		ondly         :5-0 +1,
		offdly        :11-6 +1,
		rdydly        :17-12 +1,
		enable        :18-18 +1,
		mem_ls_enable :19-19 +1,
		rsvd0         :31-20 +1;
	};
};

union mc_hub_misc_idle_status {
	uint32_t mc_hub_misc_idle_status;
	struct { uint32_t
		outstanding_cp_read    :0-0 +1,
		outstanding_cp_write   :1-1 +1,
		outstanding_gfx_read   :2-2 +1,
		outstanding_gfx_write  :3-3 +1,
		rsvd0                  :5-4 +1,
		outstanding_rlc_read   :6-6 +1,
		outstanding_rlc_write  :7-7 +1,
		rsvd1                  :9-8 +1,
		outstanding_disp_read  :10-10 +1,
		outstanding_disp_write :11-11 +1,
		outstanding_uvd_read   :12-12 +1,
		outstanding_uvd_write  :13-13 +1,
		outstanding_smu_read   :14-14 +1,
		outstanding_smu_write  :15-15 +1,
		outstanding_hdp_read   :16-16 +1,
		outstanding_hdp_write  :17-17 +1,
		outstanding_oth_read   :18-18 +1,
		outstanding_oth_write  :19-19 +1,
		outstanding_vmc_read   :20-20 +1,
		outstanding_vmc_write  :21-21 +1,
		rsvd2                  :23-22 +1,
		outstanding_vce_read   :24-24 +1,
		outstanding_vce_write  :25-25 +1,
		rsvd3                  :31-26 +1;
	};
};

union mc_hub_misc_override {
	uint32_t mc_hub_misc_override;
	struct { uint32_t
		idle   :1-0 +1,
		rsvd0  :31-2 +1;
	};
};

union mc_hub_misc_power {
	uint32_t mc_hub_misc_power;
	struct { uint32_t
		srbm_gate_override :2-2 +1,
		pm_blackout_cntl   :4-3 +1,
		rsvd0              :31-5 +1;
	};
};

union mc_hub_misc_sip_cg {
	uint32_t mc_hub_misc_sip_cg;
	struct { uint32_t
		ondly         :5-0 +1,
		offdly        :11-6 +1,
		rdydly        :17-12 +1,
		enable        :18-18 +1,
		mem_ls_enable :19-19 +1,
		rsvd0         :31-20 +1;
	};
};

union mc_hub_misc_status {
	uint32_t mc_hub_misc_status;
	struct { uint32_t
		outstanding_read       :0-0 +1,
		outstanding_write      :1-1 +1,
		outstanding_hub_rdreq  :2-2 +1,
		outstanding_hub_rdret  :3-3 +1,
		outstanding_hub_wrreq  :4-4 +1,
		outstanding_hub_wrret  :5-5 +1,
		outstanding_rpb_read   :6-6 +1,
		outstanding_rpb_write  :7-7 +1,
		outstanding_mcd_read   :8-8 +1,
		outstanding_mcd_write  :9-9 +1,
		rpb_busy               :10-10 +1,
		write_deadlock_warning :11-11 +1,
		read_deadlock_warning  :12-12 +1,
		gfx_busy               :13-13 +1,
		rsvd0                  :31-14 +1;
	};
};

union mc_hub_misc_vm_cg {
	uint32_t mc_hub_misc_vm_cg;
	struct { uint32_t
		ondly         :5-0 +1,
		offdly        :11-6 +1,
		rdydly        :17-12 +1,
		enable        :18-18 +1,
		mem_ls_enable :19-19 +1,
		rsvd0         :31-20 +1;
	};
};

union mc_hub_rdreq_cntl {
	uint32_t mc_hub_rdreq_cntl;
	struct { uint32_t
		remote_blackout        :0-0 +1,
		rsvd0                  :1-1 +1,
		jumpahead_gbl0         :2-2 +1,
		jumpahead_gbl1         :3-3 +1,
		override_stall_enable  :4-4 +1,
		mcdw_stall_mode        :5-5 +1,
		mcdx_stall_mode        :6-6 +1,
		mcdy_stall_mode        :7-7 +1,
		mcdz_stall_mode        :8-8 +1,
		break_hdp_deadlock     :9-9 +1,
		debug_reg              :16-10 +1,
		disable_self_init_gbl0 :17-17 +1,
		disable_self_init_gbl1 :18-18 +1,
		pwrxpress_mode         :19-19 +1,
		rsvd1                  :31-20 +1;
	};
};

union mc_hub_rdreq_credits2 {
	uint32_t mc_hub_rdreq_credits2;
	struct { uint32_t
		stor1_pri :7-0 +1,
		rsvd0     :31-8 +1;
	};
};

union mc_hub_rdreq_credits {
	uint32_t mc_hub_rdreq_credits;
	struct { uint32_t
		vm0    :7-0 +1,
		vm1    :15-8 +1,
		stor0  :23-16 +1,
		stor1  :31-24 +1;
	};
};

union mc_hub_rdreq_dmif {
	uint32_t mc_hub_rdreq_dmif;
	struct { uint32_t
		enable          :0-0 +1,
		rsvd0           :2-1 +1,
		blackout_exempt :3-3 +1,
		rsvd1           :10-4 +1,
		lazy_timer      :14-11 +1,
		rsvd2           :31-15 +1;
	};
};

union mc_hub_rdreq_dmif_limit {
	uint32_t mc_hub_rdreq_dmif_limit;
	struct { uint32_t
		enable      :1-0 +1,
		limit_count :6-2 +1,
		rsvd0       :31-7 +1;
	};
};

union mc_hub_rdreq_dmif {
	uint32_t mc_hub_rdreq_dmif;
	struct { uint32_t
		prescale           :2-1 +1,
		rsvd0              :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		rsvd1              :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd2              :31-16 +1;
	};
};

union mc_hub_rdreq_gbl0 {
	uint32_t mc_hub_rdreq_gbl0;
	struct { uint32_t
		stall_threshold :7-0 +1,
		rsvd0           :31-8 +1;
	};
};

union mc_hub_rdreq_gbl1 {
	uint32_t mc_hub_rdreq_gbl1;
	struct { uint32_t
		stall_threshold :7-0 +1,
		rsvd0           :31-8 +1;
	};
};

union mc_hub_rdreq_hdp {
	uint32_t mc_hub_rdreq_hdp;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_rdreq_mcdw {
	uint32_t mc_hub_rdreq_mcdw;
	struct { uint32_t
		enable          :0-0 +1,
		blackout_exempt :1-1 +1,
		bus             :2-2 +1,
		maxburst        :6-3 +1,
		lazy_timer      :10-7 +1,
		ask_credits     :17-11 +1,
		display_credits :24-18 +1,
		stall_threshold :31-25 +1;
	};
};

union mc_hub_rdreq_mcdx {
	uint32_t mc_hub_rdreq_mcdx;
	struct { uint32_t
		enable          :0-0 +1,
		blackout_exempt :1-1 +1,
		bus             :2-2 +1,
		maxburst        :6-3 +1,
		lazy_timer      :10-7 +1,
		ask_credits     :17-11 +1,
		display_credits :24-18 +1,
		stall_threshold :31-25 +1;
	};
};

union mc_hub_rdreq_mcdy {
	uint32_t mc_hub_rdreq_mcdy;
	struct { uint32_t
		enable          :0-0 +1,
		blackout_exempt :1-1 +1,
		bus             :2-2 +1,
		maxburst        :6-3 +1,
		lazy_timer      :10-7 +1,
		ask_credits     :17-11 +1,
		display_credits :24-18 +1,
		stall_threshold :31-25 +1;
	};
};

union mc_hub_rdreq_mcdz {
	uint32_t mc_hub_rdreq_mcdz;
	struct { uint32_t
		enable          :0-0 +1,
		blackout_exempt :1-1 +1,
		bus             :2-2 +1,
		maxburst        :6-3 +1,
		lazy_timer      :10-7 +1,
		ask_credits     :17-11 +1,
		display_credits :24-18 +1,
		stall_threshold :31-25 +1;
	};
};

union mc_hub_rdreq_mcif {
	uint32_t mc_hub_rdreq_mcif;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_rdreq_rlc {
	uint32_t mc_hub_rdreq_rlc;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_rdreq_sem {
	uint32_t mc_hub_rdreq_sem;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_rdreq_sip {
	uint32_t mc_hub_rdreq_sip;
	struct { uint32_t
		ask_credits     :6-0 +1,
		dummy           :7-7 +1,
		display_credits :14-8 +1,
		rsvd0           :31-15 +1;
	};
};

union mc_hub_rdreq_smu {
	uint32_t mc_hub_rdreq_smu;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_rdreq_status {
	uint32_t mc_hub_rdreq_status;
	struct { uint32_t
		sip_avail             :0-0 +1,
		mcdw_rd_avail         :1-1 +1,
		mcdx_rd_avail         :2-2 +1,
		mcdy_rd_avail         :3-3 +1,
		mcdz_rd_avail         :4-4 +1,
		gbl0_vm_full          :5-5 +1,
		gbl0_stor_full        :6-6 +1,
		gbl0_bypass_stor_full :7-7 +1,
		gbl1_vm_full          :8-8 +1,
		gbl1_stor_full        :9-9 +1,
		gbl1_bypass_stor_full :10-10 +1,
		pwrxpress_err         :11-11 +1,
		rsvd0                 :31-12 +1;
	};
};

union mc_hub_rdreq_umc {
	uint32_t mc_hub_rdreq_umc;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_rdreq_uvd {
	uint32_t mc_hub_rdreq_uvd;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		vm_bypass          :16-16 +1,
		rsvd0              :31-17 +1;
	};
};

union mc_hub_rdreq_vce {
	uint32_t mc_hub_rdreq_vce;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_rdreq_vceu {
	uint32_t mc_hub_rdreq_vceu;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_rdreq_vmc {
	uint32_t mc_hub_rdreq_vmc;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_rdreq_wtm_cntl {
	uint32_t mc_hub_rdreq_wtm_cntl;
	struct { uint32_t
		group0_decrement :2-0 +1,
		group1_decrement :5-3 +1,
		group2_decrement :8-6 +1,
		group3_decrement :11-9 +1,
		group4_decrement :14-12 +1,
		group5_decrement :17-15 +1,
		group6_decrement :20-18 +1,
		group7_decrement :23-21 +1,
		rsvd0            :31-24 +1;
	};
};

union mc_hub_rdreq_xdmam {
	uint32_t mc_hub_rdreq_xdmam;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_shared_dagb_dly {
	uint32_t mc_hub_shared_dagb_dly;
	struct { uint32_t
		dly    :5-0 +1,
		rsvd0  :15-6 +1,
		cli    :20-16 +1,
		rsvd1  :23-21 +1,
		pos    :28-24 +1,
		rsvd2  :31-29 +1;
	};
};

union mc_hub_wdp_bp {
	uint32_t mc_hub_wdp_bp;
	struct { uint32_t
		enable :0-0 +1,
		rdret  :17-1 +1,
		wrreq  :29-18 +1,
		rsvd0  :31-30 +1;
	};
};

union mc_hub_wdp_cntl {
	uint32_t mc_hub_wdp_cntl;
	struct { uint32_t
		jumpahead_gbl0             :1-1 +1,
		jumpahead_gbl1             :2-2 +1,
		jumpahead_internal         :3-3 +1,
		override_stall_enable      :4-4 +1,
		debug_reg                  :12-5 +1,
		disable_self_init_gbl0     :13-13 +1,
		disable_self_init_gbl1     :14-14 +1,
		disable_self_init_internal :15-15 +1,
		fair_ch_sw                 :16-16 +1,
		lclwrreq_bypass            :17-17 +1,
		disp_wait_eop              :18-18 +1,
		mcd_wait_eop               :19-19 +1,
		sip_wait_eop               :20-20 +1,
		rsvd0                      :31-21 +1;
	};
};

union mc_hub_wdp_credits {
	uint32_t mc_hub_wdp_credits;
	struct { uint32_t
		vm0    :7-0 +1,
		vm1    :15-8 +1,
		stor0  :23-16 +1,
		stor1  :31-24 +1;
	};
};

union mc_hub_wdp_err {
	uint32_t mc_hub_wdp_err;
	struct { uint32_t
		mgpu1_targ_sys :0-0 +1,
		mgpu2_targ_sys :1-1 +1,
		rsvd0          :31-2 +1;
	};
};

union mc_hub_wdp_gbl0 {
	uint32_t mc_hub_wdp_gbl0;
	struct { uint32_t
		maxburst        :3-0 +1,
		lazy_timer      :7-4 +1,
		stall_threshold :15-8 +1,
		stall_mode      :16-16 +1,
		rsvd0           :31-17 +1;
	};
};

union mc_hub_wdp_gbl1 {
	uint32_t mc_hub_wdp_gbl1;
	struct { uint32_t
		maxburst        :3-0 +1,
		lazy_timer      :7-4 +1,
		stall_threshold :15-8 +1,
		stall_mode      :16-16 +1,
		rsvd0           :31-17 +1;
	};
};

union mc_hub_wdp_hdp {
	uint32_t mc_hub_wdp_hdp;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_ih {
	uint32_t mc_hub_wdp_ih;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_mcdw {
	uint32_t mc_hub_wdp_mcdw;
	struct { uint32_t
		enable          :0-0 +1,
		blackout_exempt :1-1 +1,
		stall_mode      :2-2 +1,
		maxburst        :6-3 +1,
		ask_credits     :12-7 +1,
		lazy_timer      :16-13 +1,
		stall_threshold :23-17 +1,
		ask_credits_w   :30-24 +1,
		rsvd0           :31-31 +1;
	};
};

union mc_hub_wdp_mcdx {
	uint32_t mc_hub_wdp_mcdx;
	struct { uint32_t
		enable          :0-0 +1,
		blackout_exempt :1-1 +1,
		stall_mode      :2-2 +1,
		maxburst        :6-3 +1,
		ask_credits     :12-7 +1,
		lazy_timer      :16-13 +1,
		stall_threshold :23-17 +1,
		ask_credits_w   :30-24 +1,
		rsvd0           :31-31 +1;
	};
};

union mc_hub_wdp_mcdy {
	uint32_t mc_hub_wdp_mcdy;
	struct { uint32_t
		enable          :0-0 +1,
		blackout_exempt :1-1 +1,
		stall_mode      :2-2 +1,
		maxburst        :6-3 +1,
		ask_credits     :12-7 +1,
		lazy_timer      :16-13 +1,
		stall_threshold :23-17 +1,
		ask_credits_w   :30-24 +1,
		rsvd0           :31-31 +1;
	};
};

union mc_hub_wdp_mcdz {
	uint32_t mc_hub_wdp_mcdz;
	struct { uint32_t
		enable          :0-0 +1,
		blackout_exempt :1-1 +1,
		stall_mode      :2-2 +1,
		maxburst        :6-3 +1,
		ask_credits     :12-7 +1,
		lazy_timer      :16-13 +1,
		stall_threshold :23-17 +1,
		ask_credits_w   :30-24 +1,
		rsvd0           :31-31 +1;
	};
};

union mc_hub_wdp_mcif {
	uint32_t mc_hub_wdp_mcif;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_mgpu2 {
	uint32_t mc_hub_wdp_mgpu2;
	struct { uint32_t
		cid2   :7-0 +1,
		rsvd0  :31-8 +1;
	};
};

union mc_hub_wdp_mgpu {
	uint32_t mc_hub_wdp_mgpu;
	struct { uint32_t
		stor               :7-0 +1,
		cid                :15-8 +1,
		mgpu_priority_time :22-16 +1,
		enable             :23-23 +1,
		oth_priority_time  :30-24 +1,
		rsvd0              :31-31 +1;
	};
};

union mc_hub_wdp_rlc {
	uint32_t mc_hub_wdp_rlc;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_sem {
	uint32_t mc_hub_wdp_sem;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_sh0 {
	uint32_t mc_hub_wdp_sh0;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_sh1 {
	uint32_t mc_hub_wdp_sh1;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_sip {
	uint32_t mc_hub_wdp_sip;
	struct { uint32_t
		stall_mode  :1-0 +1,
		ask_credits :8-2 +1,
		rsvd0       :31-9 +1;
	};
};

union mc_hub_wdp_smu {
	uint32_t mc_hub_wdp_smu;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_status {
	uint32_t mc_hub_wdp_status;
	struct { uint32_t
		sip_avail             :0-0 +1,
		mcdw_rd_avail         :1-1 +1,
		mcdx_rd_avail         :2-2 +1,
		mcdy_rd_avail         :3-3 +1,
		mcdz_rd_avail         :4-4 +1,
		gbl0_vm_full          :5-5 +1,
		gbl0_stor_full        :6-6 +1,
		gbl0_bypass_stor_full :7-7 +1,
		gbl1_vm_full          :8-8 +1,
		gbl1_stor_full        :9-9 +1,
		gbl1_bypass_stor_full :10-10 +1,
		mcdw_wr_avail         :11-11 +1,
		mcdx_wr_avail         :12-12 +1,
		mcdy_wr_avail         :13-13 +1,
		mcdz_wr_avail         :14-14 +1,
		rsvd0                 :31-15 +1;
	};
};

union mc_hub_wdp_umc {
	uint32_t mc_hub_wdp_umc;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_uvd {
	uint32_t mc_hub_wdp_uvd;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		vm_bypass          :16-16 +1,
		rsvd0              :31-17 +1;
	};
};

union mc_hub_wdp_vce {
	uint32_t mc_hub_wdp_vce;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_vceu {
	uint32_t mc_hub_wdp_vceu;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wdp_wtm_cntl {
	uint32_t mc_hub_wdp_wtm_cntl;
	struct { uint32_t
		group0_decrement :2-0 +1,
		group1_decrement :5-3 +1,
		group2_decrement :8-6 +1,
		group3_decrement :11-9 +1,
		group4_decrement :14-12 +1,
		group5_decrement :17-15 +1,
		group6_decrement :20-18 +1,
		group7_decrement :23-21 +1,
		rsvd0            :31-24 +1;
	};
};

union mc_hub_wdp_xdma {
	uint32_t mc_hub_wdp_xdma;
	struct { uint32_t
		enable                :0-0 +1,
		rsvd0                 :2-1 +1,
		blackout_exempt       :3-3 +1,
		rsvd1                 :6-4 +1,
		maxburst              :10-7 +1,
		lazy_timer            :14-11 +1,
		rsvd2                 :15-15 +1,
		bypass_avail_override :16-16 +1,
		rsvd3                 :31-17 +1;
	};
};

union mc_hub_wdp_xdmam {
	uint32_t mc_hub_wdp_xdmam;
	struct { uint32_t
		enable                :0-0 +1,
		prescale              :2-1 +1,
		blackout_exempt       :3-3 +1,
		stall_mode            :5-4 +1,
		stall_override        :6-6 +1,
		maxburst              :10-7 +1,
		lazy_timer            :14-11 +1,
		stall_override_wtm    :15-15 +1,
		bypass_avail_override :16-16 +1,
		rsvd0                 :31-17 +1;
	};
};

union mc_hub_wdp_xdma {
	uint32_t mc_hub_wdp_xdma;
	struct { uint32_t
		prescale           :2-1 +1,
		rsvd0              :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		rsvd1              :14-7 +1,
		stall_override_wtm :15-15 +1,
		rsvd2              :31-16 +1;
	};
};

union mc_hub_wdp_xdp {
	uint32_t mc_hub_wdp_xdp;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		maxburst           :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_hub_wrret_cntl {
	uint32_t mc_hub_wrret_cntl;
	struct { uint32_t
		jumpahead         :0-0 +1,
		bp                :20-1 +1,
		bp_enable         :21-21 +1,
		debug_reg         :29-22 +1,
		disable_self_init :30-30 +1,
		fair_ch_sw        :31-31 +1;
	};
};

union mc_hub_wrret_mcdw {
	uint32_t mc_hub_wrret_mcdw;
	struct { uint32_t
		stall_mode   :0-0 +1,
		credit_count :7-1 +1,
		rsvd0        :31-8 +1;
	};
};

union mc_hub_wrret_mcdx {
	uint32_t mc_hub_wrret_mcdx;
	struct { uint32_t
		stall_mode   :0-0 +1,
		credit_count :7-1 +1,
		rsvd0        :31-8 +1;
	};
};

union mc_hub_wrret_mcdy {
	uint32_t mc_hub_wrret_mcdy;
	struct { uint32_t
		stall_mode   :0-0 +1,
		credit_count :7-1 +1,
		rsvd0        :31-8 +1;
	};
};

union mc_hub_wrret_mcdz {
	uint32_t mc_hub_wrret_mcdz;
	struct { uint32_t
		stall_mode   :0-0 +1,
		credit_count :7-1 +1,
		rsvd0        :31-8 +1;
	};
};

union mc_hub_wrret_status {
	uint32_t mc_hub_wrret_status;
	struct { uint32_t
		mcdw_avail :0-0 +1,
		mcdx_avail :1-1 +1,
		mcdy_avail :2-2 +1,
		mcdz_avail :3-3 +1,
		rsvd0      :31-4 +1;
	};
};

union mc_imp_cntl {
	uint32_t mc_imp_cntl;
	struct { uint32_t
		mem_io_update_rate :4-0 +1,
		cal_vref_sel       :5-5 +1,
		cal_vrefmode       :6-6 +1,
		rsvd0              :7-7 +1,
		timeout_err        :8-8 +1,
		clear_timeout_err  :9-9 +1,
		rsvd1              :12-10 +1,
		mem_io_sample_cnt  :15-13 +1,
		cal_vref           :22-16 +1,
		rsvd2              :28-23 +1,
		cal_when_idle      :29-29 +1,
		cal_when_refresh   :30-30 +1,
		cal_pwron          :31-31 +1;
	};
};

union mc_imp_debug {
	uint32_t mc_imp_debug;
	struct { uint32_t
		tstartup_cntr   :7-0 +1,
		timeout_cntr    :15-8 +1,
		pmvcal_reserved :27-16 +1,
		debug_cal_en    :28-28 +1,
		debug_cal_start :29-29 +1,
		debug_cal_intr  :30-30 +1,
		debug_cal_done  :31-31 +1;
	};
};

union mc_imp_dq_status {
	uint32_t mc_imp_dq_status;
	struct { uint32_t
		ch0_dq_pstr :7-0 +1,
		ch0_dq_nstr :15-8 +1,
		ch1_dq_pstr :23-16 +1,
		ch1_dq_nstr :31-24 +1;
	};
};

union mc_imp_status {
	uint32_t mc_imp_status;
	struct { uint32_t
		pstr_cal       :7-0 +1,
		pstr_accum_val :15-8 +1,
		nstr_cal       :23-16 +1,
		nstr_accum_val :31-24 +1;
	};
};

union mc_io_aphy_str_cntl_d0 {
	uint32_t mc_io_aphy_str_cntl_d0;
	struct { uint32_t
		pstr_off_a    :5-0 +1,
		nstr_off_a    :11-6 +1,
		pstr_off_d_rd :17-12 +1,
		rsvd0         :23-18 +1,
		use_a_cal     :24-24 +1,
		use_d_rd_cal  :25-25 +1,
		cal_sel       :27-26 +1,
		load_a_str    :28-28 +1,
		load_d_rd_str :29-29 +1,
		rsvd1         :31-30 +1;
	};
};

union mc_io_aphy_str_cntl_d1 {
	uint32_t mc_io_aphy_str_cntl_d1;
	struct { uint32_t
		pstr_off_a    :5-0 +1,
		nstr_off_a    :11-6 +1,
		pstr_off_d_rd :17-12 +1,
		rsvd0         :23-18 +1,
		use_a_cal     :24-24 +1,
		use_d_rd_cal  :25-25 +1,
		cal_sel       :27-26 +1,
		load_a_str    :28-28 +1,
		load_d_rd_str :29-29 +1,
		rsvd1         :31-30 +1;
	};
};

union mc_io_cdrcntl1_d0 {
	uint32_t mc_io_cdrcntl1_d0;
	struct { uint32_t
		dq_rxphase_b0   :7-0 +1,
		dq_rxphase_b1   :15-8 +1,
		wcdr_txphase_b0 :23-16 +1,
		wcdr_txphase_b1 :31-24 +1;
	};
};

union mc_io_cdrcntl1_d1 {
	uint32_t mc_io_cdrcntl1_d1;
	struct { uint32_t
		dq_rxphase_b0   :7-0 +1,
		dq_rxphase_b1   :15-8 +1,
		wcdr_txphase_b0 :23-16 +1,
		wcdr_txphase_b1 :31-24 +1;
	};
};

union mc_io_cdrcntl2_d0 {
	uint32_t mc_io_cdrcntl2_d0;
	struct { uint32_t
		cdr_fb_sel0   :0-0 +1,
		cdr_fb_sel1   :1-1 +1,
		edc_rxen_ovr0 :2-2 +1,
		edc_rxen_ovr1 :3-3 +1,
		txcdrbypass0  :4-4 +1,
		txcdrbypass1  :5-5 +1,
		wck_rxen_ovr0 :6-6 +1,
		wck_rxen_ovr1 :7-7 +1,
		rsvd0         :31-8 +1;
	};
};

union mc_io_cdrcntl2_d1 {
	uint32_t mc_io_cdrcntl2_d1;
	struct { uint32_t
		cdr_fb_sel0   :0-0 +1,
		cdr_fb_sel1   :1-1 +1,
		edc_rxen_ovr0 :2-2 +1,
		edc_rxen_ovr1 :3-3 +1,
		txcdrbypass0  :4-4 +1,
		txcdrbypass1  :5-5 +1,
		wck_rxen_ovr0 :6-6 +1,
		wck_rxen_ovr1 :7-7 +1,
		rsvd0         :31-8 +1;
	};
};

union mc_io_cdrcntl_d0 {
	uint32_t mc_io_cdrcntl_d0;
	struct { uint32_t
		rxphase_b01     :3-0 +1,
		rxphase_b23     :7-4 +1,
		rxcdren_b01     :8-8 +1,
		rxcdren_b23     :9-9 +1,
		rxcdrbypass_b01 :10-10 +1,
		rxcdrbypass_b23 :11-11 +1,
		rxphase1_b01    :15-12 +1,
		rxphase1_b23    :19-16 +1,
		dqtxcdren_b0    :20-20 +1,
		dqtxcdren_b1    :21-21 +1,
		dqrxcdren_b0    :22-22 +1,
		dqrxcdren_b1    :23-23 +1,
		wcdrrxcdren_b0  :24-24 +1,
		wcdrrxcdren_b1  :25-25 +1,
		wcdredc_b0      :26-26 +1,
		wcdredc_b1      :27-27 +1,
		dqrxsel_b0      :28-28 +1,
		dqrxsel_b1      :29-29 +1,
		dqtxsel_b0      :30-30 +1,
		dqtxsel_b1      :31-31 +1;
	};
};

union mc_io_cdrcntl_d1 {
	uint32_t mc_io_cdrcntl_d1;
	struct { uint32_t
		rxphase_b01     :3-0 +1,
		rxphase_b23     :7-4 +1,
		rxcdren_b01     :8-8 +1,
		rxcdren_b23     :9-9 +1,
		rxcdrbypass_b01 :10-10 +1,
		rxcdrbypass_b23 :11-11 +1,
		rxphase1_b01    :15-12 +1,
		rxphase1_b23    :19-16 +1,
		dqtxcdren_b0    :20-20 +1,
		dqtxcdren_b1    :21-21 +1,
		dqrxcdren_b0    :22-22 +1,
		dqrxcdren_b1    :23-23 +1,
		wcdrrxcdren_b0  :24-24 +1,
		wcdrrxcdren_b1  :25-25 +1,
		wcdredc_b0      :26-26 +1,
		wcdredc_b1      :27-27 +1,
		dqrxsel_b0      :28-28 +1,
		dqrxsel_b1      :29-29 +1,
		dqtxsel_b0      :30-30 +1,
		dqtxsel_b1      :31-31 +1;
	};
};

union mc_io_debug_acmd_clksel_d0 {
	uint32_t mc_io_debug_acmd_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_clksel_d1 {
	uint32_t mc_io_debug_acmd_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_misc_d0 {
	uint32_t mc_io_debug_acmd_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_misc_d1 {
	uint32_t mc_io_debug_acmd_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_ofscal_d0 {
	uint32_t mc_io_debug_acmd_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_ofscal_d1 {
	uint32_t mc_io_debug_acmd_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_rxphase_d0 {
	uint32_t mc_io_debug_acmd_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_rxphase_d1 {
	uint32_t mc_io_debug_acmd_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_txbst_pd_d0 {
	uint32_t mc_io_debug_acmd_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_txbst_pd_d1 {
	uint32_t mc_io_debug_acmd_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_txbst_pu_d0 {
	uint32_t mc_io_debug_acmd_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_txbst_pu_d1 {
	uint32_t mc_io_debug_acmd_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_txphase_d0 {
	uint32_t mc_io_debug_acmd_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_txphase_d1 {
	uint32_t mc_io_debug_acmd_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_txslf_d0 {
	uint32_t mc_io_debug_acmd_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_acmd_txslf_d1 {
	uint32_t mc_io_debug_acmd_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_clksel_d0 {
	uint32_t mc_io_debug_addrh_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_clksel_d1 {
	uint32_t mc_io_debug_addrh_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_misc_d0 {
	uint32_t mc_io_debug_addrh_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_misc_d1 {
	uint32_t mc_io_debug_addrh_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_rxphase_d0 {
	uint32_t mc_io_debug_addrh_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_rxphase_d1 {
	uint32_t mc_io_debug_addrh_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_txbst_pd_d0 {
	uint32_t mc_io_debug_addrh_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_txbst_pd_d1 {
	uint32_t mc_io_debug_addrh_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_txbst_pu_d0 {
	uint32_t mc_io_debug_addrh_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_txbst_pu_d1 {
	uint32_t mc_io_debug_addrh_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_txphase_d0 {
	uint32_t mc_io_debug_addrh_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_txphase_d1 {
	uint32_t mc_io_debug_addrh_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_txslf_d0 {
	uint32_t mc_io_debug_addrh_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrh_txslf_d1 {
	uint32_t mc_io_debug_addrh_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_clksel_d0 {
	uint32_t mc_io_debug_addrl_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_clksel_d1 {
	uint32_t mc_io_debug_addrl_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_misc_d0 {
	uint32_t mc_io_debug_addrl_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_misc_d1 {
	uint32_t mc_io_debug_addrl_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_rxphase_d0 {
	uint32_t mc_io_debug_addrl_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_rxphase_d1 {
	uint32_t mc_io_debug_addrl_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_txbst_pd_d0 {
	uint32_t mc_io_debug_addrl_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_txbst_pd_d1 {
	uint32_t mc_io_debug_addrl_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_txbst_pu_d0 {
	uint32_t mc_io_debug_addrl_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_txbst_pu_d1 {
	uint32_t mc_io_debug_addrl_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_txphase_d0 {
	uint32_t mc_io_debug_addrl_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_txphase_d1 {
	uint32_t mc_io_debug_addrl_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_txslf_d0 {
	uint32_t mc_io_debug_addrl_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_addrl_txslf_d1 {
	uint32_t mc_io_debug_addrl_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_clksel_d0 {
	uint32_t mc_io_debug_ck_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_clksel_d1 {
	uint32_t mc_io_debug_ck_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_misc_d0 {
	uint32_t mc_io_debug_ck_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_misc_d1 {
	uint32_t mc_io_debug_ck_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_rxphase_d0 {
	uint32_t mc_io_debug_ck_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_rxphase_d1 {
	uint32_t mc_io_debug_ck_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_txbst_pd_d0 {
	uint32_t mc_io_debug_ck_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_txbst_pd_d1 {
	uint32_t mc_io_debug_ck_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_txbst_pu_d0 {
	uint32_t mc_io_debug_ck_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_txbst_pu_d1 {
	uint32_t mc_io_debug_ck_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_txphase_d0 {
	uint32_t mc_io_debug_ck_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_txphase_d1 {
	uint32_t mc_io_debug_ck_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_txslf_d0 {
	uint32_t mc_io_debug_ck_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_ck_txslf_d1 {
	uint32_t mc_io_debug_ck_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_clksel_d0 {
	uint32_t mc_io_debug_cmd_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_clksel_d1 {
	uint32_t mc_io_debug_cmd_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_misc_d0 {
	uint32_t mc_io_debug_cmd_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_misc_d1 {
	uint32_t mc_io_debug_cmd_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_ofscal_d0 {
	uint32_t mc_io_debug_cmd_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_ofscal_d1 {
	uint32_t mc_io_debug_cmd_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_rx_eq_d0 {
	uint32_t mc_io_debug_cmd_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_rx_eq_d1 {
	uint32_t mc_io_debug_cmd_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_rxphase_d0 {
	uint32_t mc_io_debug_cmd_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_rxphase_d1 {
	uint32_t mc_io_debug_cmd_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_txbst_pd_d0 {
	uint32_t mc_io_debug_cmd_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_txbst_pd_d1 {
	uint32_t mc_io_debug_cmd_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_txbst_pu_d0 {
	uint32_t mc_io_debug_cmd_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_txbst_pu_d1 {
	uint32_t mc_io_debug_cmd_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_txphase_d0 {
	uint32_t mc_io_debug_cmd_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_txphase_d1 {
	uint32_t mc_io_debug_cmd_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_txslf_d0 {
	uint32_t mc_io_debug_cmd_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_cmd_txslf_d1 {
	uint32_t mc_io_debug_cmd_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_cdr_phsize_d0 {
	uint32_t mc_io_debug_dbi_cdr_phsize_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_cdr_phsize_d1 {
	uint32_t mc_io_debug_dbi_cdr_phsize_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_clksel_d0 {
	uint32_t mc_io_debug_dbi_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_clksel_d1 {
	uint32_t mc_io_debug_dbi_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_misc_d0 {
	uint32_t mc_io_debug_dbi_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_misc_d1 {
	uint32_t mc_io_debug_dbi_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_ofscal_d0 {
	uint32_t mc_io_debug_dbi_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_ofscal_d1 {
	uint32_t mc_io_debug_dbi_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_rx_eq_d0 {
	uint32_t mc_io_debug_dbi_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_rx_eq_d1 {
	uint32_t mc_io_debug_dbi_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_rxphase_d0 {
	uint32_t mc_io_debug_dbi_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_rxphase_d1 {
	uint32_t mc_io_debug_dbi_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_rx_vref_cal_d0 {
	uint32_t mc_io_debug_dbi_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_rx_vref_cal_d1 {
	uint32_t mc_io_debug_dbi_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_txbst_pd_d0 {
	uint32_t mc_io_debug_dbi_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_txbst_pd_d1 {
	uint32_t mc_io_debug_dbi_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_txbst_pu_d0 {
	uint32_t mc_io_debug_dbi_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_txbst_pu_d1 {
	uint32_t mc_io_debug_dbi_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_txphase_d0 {
	uint32_t mc_io_debug_dbi_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_txphase_d1 {
	uint32_t mc_io_debug_dbi_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_txslf_d0 {
	uint32_t mc_io_debug_dbi_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dbi_txslf_d1 {
	uint32_t mc_io_debug_dbi_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dq0_rx_dyn_pm_d0 {
	uint32_t mc_io_debug_dq0_rx_dyn_pm_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dq0_rx_dyn_pm_d1 {
	uint32_t mc_io_debug_dq0_rx_dyn_pm_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dq0_rx_eq_pm_d0 {
	uint32_t mc_io_debug_dq0_rx_eq_pm_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dq0_rx_eq_pm_d1 {
	uint32_t mc_io_debug_dq0_rx_eq_pm_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dq1_rx_dyn_pm_d0 {
	uint32_t mc_io_debug_dq1_rx_dyn_pm_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dq1_rx_dyn_pm_d1 {
	uint32_t mc_io_debug_dq1_rx_dyn_pm_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dq1_rx_eq_pm_d0 {
	uint32_t mc_io_debug_dq1_rx_eq_pm_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dq1_rx_eq_pm_d1 {
	uint32_t mc_io_debug_dq1_rx_eq_pm_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0_cdr_phsize_d0 {
	uint32_t mc_io_debug_dqb0_cdr_phsize_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0_cdr_phsize_d1 {
	uint32_t mc_io_debug_dqb0_cdr_phsize_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_clksel_d0 {
	uint32_t mc_io_debug_dqb0h_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_clksel_d1 {
	uint32_t mc_io_debug_dqb0h_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_misc_d0 {
	uint32_t mc_io_debug_dqb0h_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_misc_d1 {
	uint32_t mc_io_debug_dqb0h_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_ofscal_d0 {
	uint32_t mc_io_debug_dqb0h_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_ofscal_d1 {
	uint32_t mc_io_debug_dqb0h_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_rx_eq_d0 {
	uint32_t mc_io_debug_dqb0h_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_rx_eq_d1 {
	uint32_t mc_io_debug_dqb0h_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_rxphase_d0 {
	uint32_t mc_io_debug_dqb0h_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_rxphase_d1 {
	uint32_t mc_io_debug_dqb0h_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_rx_vref_cal_d0 {
	uint32_t mc_io_debug_dqb0h_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_rx_vref_cal_d1 {
	uint32_t mc_io_debug_dqb0h_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_txbst_pd_d0 {
	uint32_t mc_io_debug_dqb0h_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_txbst_pd_d1 {
	uint32_t mc_io_debug_dqb0h_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_txbst_pu_d0 {
	uint32_t mc_io_debug_dqb0h_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_txbst_pu_d1 {
	uint32_t mc_io_debug_dqb0h_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_txphase_d0 {
	uint32_t mc_io_debug_dqb0h_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_txphase_d1 {
	uint32_t mc_io_debug_dqb0h_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_txslf_d0 {
	uint32_t mc_io_debug_dqb0h_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0h_txslf_d1 {
	uint32_t mc_io_debug_dqb0h_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_clksel_d0 {
	uint32_t mc_io_debug_dqb0l_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_clksel_d1 {
	uint32_t mc_io_debug_dqb0l_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_misc_d0 {
	uint32_t mc_io_debug_dqb0l_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_misc_d1 {
	uint32_t mc_io_debug_dqb0l_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_ofscal_d0 {
	uint32_t mc_io_debug_dqb0l_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_ofscal_d1 {
	uint32_t mc_io_debug_dqb0l_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_rx_eq_d0 {
	uint32_t mc_io_debug_dqb0l_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_rx_eq_d1 {
	uint32_t mc_io_debug_dqb0l_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_rxphase_d0 {
	uint32_t mc_io_debug_dqb0l_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_rxphase_d1 {
	uint32_t mc_io_debug_dqb0l_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_rx_vref_cal_d0 {
	uint32_t mc_io_debug_dqb0l_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_rx_vref_cal_d1 {
	uint32_t mc_io_debug_dqb0l_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_txbst_pd_d0 {
	uint32_t mc_io_debug_dqb0l_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_txbst_pd_d1 {
	uint32_t mc_io_debug_dqb0l_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_txbst_pu_d0 {
	uint32_t mc_io_debug_dqb0l_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_txbst_pu_d1 {
	uint32_t mc_io_debug_dqb0l_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_txphase_d0 {
	uint32_t mc_io_debug_dqb0l_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_txphase_d1 {
	uint32_t mc_io_debug_dqb0l_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_txslf_d0 {
	uint32_t mc_io_debug_dqb0l_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb0l_txslf_d1 {
	uint32_t mc_io_debug_dqb0l_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1_cdr_phsize_d0 {
	uint32_t mc_io_debug_dqb1_cdr_phsize_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1_cdr_phsize_d1 {
	uint32_t mc_io_debug_dqb1_cdr_phsize_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_clksel_d0 {
	uint32_t mc_io_debug_dqb1h_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_clksel_d1 {
	uint32_t mc_io_debug_dqb1h_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_misc_d0 {
	uint32_t mc_io_debug_dqb1h_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_misc_d1 {
	uint32_t mc_io_debug_dqb1h_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_ofscal_d0 {
	uint32_t mc_io_debug_dqb1h_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_ofscal_d1 {
	uint32_t mc_io_debug_dqb1h_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_rx_eq_d0 {
	uint32_t mc_io_debug_dqb1h_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_rx_eq_d1 {
	uint32_t mc_io_debug_dqb1h_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_rxphase_d0 {
	uint32_t mc_io_debug_dqb1h_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_rxphase_d1 {
	uint32_t mc_io_debug_dqb1h_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_rx_vref_cal_d0 {
	uint32_t mc_io_debug_dqb1h_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_rx_vref_cal_d1 {
	uint32_t mc_io_debug_dqb1h_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_txbst_pd_d0 {
	uint32_t mc_io_debug_dqb1h_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_txbst_pd_d1 {
	uint32_t mc_io_debug_dqb1h_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_txbst_pu_d0 {
	uint32_t mc_io_debug_dqb1h_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_txbst_pu_d1 {
	uint32_t mc_io_debug_dqb1h_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_txphase_d0 {
	uint32_t mc_io_debug_dqb1h_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_txphase_d1 {
	uint32_t mc_io_debug_dqb1h_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_txslf_d0 {
	uint32_t mc_io_debug_dqb1h_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1h_txslf_d1 {
	uint32_t mc_io_debug_dqb1h_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_clksel_d0 {
	uint32_t mc_io_debug_dqb1l_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_clksel_d1 {
	uint32_t mc_io_debug_dqb1l_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_misc_d0 {
	uint32_t mc_io_debug_dqb1l_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_misc_d1 {
	uint32_t mc_io_debug_dqb1l_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_ofscal_d0 {
	uint32_t mc_io_debug_dqb1l_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_ofscal_d1 {
	uint32_t mc_io_debug_dqb1l_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_rx_eq_d0 {
	uint32_t mc_io_debug_dqb1l_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_rx_eq_d1 {
	uint32_t mc_io_debug_dqb1l_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_rxphase_d0 {
	uint32_t mc_io_debug_dqb1l_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_rxphase_d1 {
	uint32_t mc_io_debug_dqb1l_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_rx_vref_cal_d0 {
	uint32_t mc_io_debug_dqb1l_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_rx_vref_cal_d1 {
	uint32_t mc_io_debug_dqb1l_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_txbst_pd_d0 {
	uint32_t mc_io_debug_dqb1l_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_txbst_pd_d1 {
	uint32_t mc_io_debug_dqb1l_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_txbst_pu_d0 {
	uint32_t mc_io_debug_dqb1l_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_txbst_pu_d1 {
	uint32_t mc_io_debug_dqb1l_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_txphase_d0 {
	uint32_t mc_io_debug_dqb1l_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_txphase_d1 {
	uint32_t mc_io_debug_dqb1l_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_txslf_d0 {
	uint32_t mc_io_debug_dqb1l_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb1l_txslf_d1 {
	uint32_t mc_io_debug_dqb1l_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2_cdr_phsize_d0 {
	uint32_t mc_io_debug_dqb2_cdr_phsize_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2_cdr_phsize_d1 {
	uint32_t mc_io_debug_dqb2_cdr_phsize_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_clksel_d0 {
	uint32_t mc_io_debug_dqb2h_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_clksel_d1 {
	uint32_t mc_io_debug_dqb2h_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_misc_d0 {
	uint32_t mc_io_debug_dqb2h_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_misc_d1 {
	uint32_t mc_io_debug_dqb2h_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_ofscal_d0 {
	uint32_t mc_io_debug_dqb2h_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_ofscal_d1 {
	uint32_t mc_io_debug_dqb2h_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_rx_eq_d0 {
	uint32_t mc_io_debug_dqb2h_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_rx_eq_d1 {
	uint32_t mc_io_debug_dqb2h_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_rxphase_d0 {
	uint32_t mc_io_debug_dqb2h_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_rxphase_d1 {
	uint32_t mc_io_debug_dqb2h_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_rx_vref_cal_d0 {
	uint32_t mc_io_debug_dqb2h_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_rx_vref_cal_d1 {
	uint32_t mc_io_debug_dqb2h_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_txbst_pd_d0 {
	uint32_t mc_io_debug_dqb2h_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_txbst_pd_d1 {
	uint32_t mc_io_debug_dqb2h_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_txbst_pu_d0 {
	uint32_t mc_io_debug_dqb2h_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_txbst_pu_d1 {
	uint32_t mc_io_debug_dqb2h_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_txphase_d0 {
	uint32_t mc_io_debug_dqb2h_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_txphase_d1 {
	uint32_t mc_io_debug_dqb2h_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_txslf_d0 {
	uint32_t mc_io_debug_dqb2h_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2h_txslf_d1 {
	uint32_t mc_io_debug_dqb2h_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_clksel_d0 {
	uint32_t mc_io_debug_dqb2l_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_clksel_d1 {
	uint32_t mc_io_debug_dqb2l_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_misc_d0 {
	uint32_t mc_io_debug_dqb2l_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_misc_d1 {
	uint32_t mc_io_debug_dqb2l_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_ofscal_d0 {
	uint32_t mc_io_debug_dqb2l_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_ofscal_d1 {
	uint32_t mc_io_debug_dqb2l_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_rx_eq_d0 {
	uint32_t mc_io_debug_dqb2l_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_rx_eq_d1 {
	uint32_t mc_io_debug_dqb2l_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_rxphase_d0 {
	uint32_t mc_io_debug_dqb2l_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_rxphase_d1 {
	uint32_t mc_io_debug_dqb2l_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_rx_vref_cal_d0 {
	uint32_t mc_io_debug_dqb2l_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_rx_vref_cal_d1 {
	uint32_t mc_io_debug_dqb2l_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_txbst_pd_d0 {
	uint32_t mc_io_debug_dqb2l_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_txbst_pd_d1 {
	uint32_t mc_io_debug_dqb2l_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_txbst_pu_d0 {
	uint32_t mc_io_debug_dqb2l_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_txbst_pu_d1 {
	uint32_t mc_io_debug_dqb2l_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_txphase_d0 {
	uint32_t mc_io_debug_dqb2l_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_txphase_d1 {
	uint32_t mc_io_debug_dqb2l_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_txslf_d0 {
	uint32_t mc_io_debug_dqb2l_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb2l_txslf_d1 {
	uint32_t mc_io_debug_dqb2l_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3_cdr_phsize_d0 {
	uint32_t mc_io_debug_dqb3_cdr_phsize_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3_cdr_phsize_d1 {
	uint32_t mc_io_debug_dqb3_cdr_phsize_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_clksel_d0 {
	uint32_t mc_io_debug_dqb3h_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_clksel_d1 {
	uint32_t mc_io_debug_dqb3h_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_misc_d0 {
	uint32_t mc_io_debug_dqb3h_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_misc_d1 {
	uint32_t mc_io_debug_dqb3h_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_ofscal_d0 {
	uint32_t mc_io_debug_dqb3h_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_ofscal_d1 {
	uint32_t mc_io_debug_dqb3h_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_rx_eq_d0 {
	uint32_t mc_io_debug_dqb3h_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_rx_eq_d1 {
	uint32_t mc_io_debug_dqb3h_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_rxphase_d0 {
	uint32_t mc_io_debug_dqb3h_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_rxphase_d1 {
	uint32_t mc_io_debug_dqb3h_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_rx_vref_cal_d0 {
	uint32_t mc_io_debug_dqb3h_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_rx_vref_cal_d1 {
	uint32_t mc_io_debug_dqb3h_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_txbst_pd_d0 {
	uint32_t mc_io_debug_dqb3h_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_txbst_pd_d1 {
	uint32_t mc_io_debug_dqb3h_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_txbst_pu_d0 {
	uint32_t mc_io_debug_dqb3h_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_txbst_pu_d1 {
	uint32_t mc_io_debug_dqb3h_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_txphase_d0 {
	uint32_t mc_io_debug_dqb3h_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_txphase_d1 {
	uint32_t mc_io_debug_dqb3h_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_txslf_d0 {
	uint32_t mc_io_debug_dqb3h_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3h_txslf_d1 {
	uint32_t mc_io_debug_dqb3h_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_clksel_d0 {
	uint32_t mc_io_debug_dqb3l_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_clksel_d1 {
	uint32_t mc_io_debug_dqb3l_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_misc_d0 {
	uint32_t mc_io_debug_dqb3l_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_misc_d1 {
	uint32_t mc_io_debug_dqb3l_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_ofscal_d0 {
	uint32_t mc_io_debug_dqb3l_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_ofscal_d1 {
	uint32_t mc_io_debug_dqb3l_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_rx_eq_d0 {
	uint32_t mc_io_debug_dqb3l_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_rx_eq_d1 {
	uint32_t mc_io_debug_dqb3l_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_rxphase_d0 {
	uint32_t mc_io_debug_dqb3l_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_rxphase_d1 {
	uint32_t mc_io_debug_dqb3l_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_rx_vref_cal_d0 {
	uint32_t mc_io_debug_dqb3l_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_rx_vref_cal_d1 {
	uint32_t mc_io_debug_dqb3l_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_txbst_pd_d0 {
	uint32_t mc_io_debug_dqb3l_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_txbst_pd_d1 {
	uint32_t mc_io_debug_dqb3l_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_txbst_pu_d0 {
	uint32_t mc_io_debug_dqb3l_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_txbst_pu_d1 {
	uint32_t mc_io_debug_dqb3l_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_txphase_d0 {
	uint32_t mc_io_debug_dqb3l_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_txphase_d1 {
	uint32_t mc_io_debug_dqb3l_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_txslf_d0 {
	uint32_t mc_io_debug_dqb3l_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_dqb3l_txslf_d1 {
	uint32_t mc_io_debug_dqb3l_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_cdr_phsize_d0 {
	uint32_t mc_io_debug_edc_cdr_phsize_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_cdr_phsize_d1 {
	uint32_t mc_io_debug_edc_cdr_phsize_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_clksel_d0 {
	uint32_t mc_io_debug_edc_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_clksel_d1 {
	uint32_t mc_io_debug_edc_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_misc_d0 {
	uint32_t mc_io_debug_edc_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_misc_d1 {
	uint32_t mc_io_debug_edc_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_ofscal_d0 {
	uint32_t mc_io_debug_edc_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_ofscal_d1 {
	uint32_t mc_io_debug_edc_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rx_dyn_pm_d0 {
	uint32_t mc_io_debug_edc_rx_dyn_pm_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rx_dyn_pm_d1 {
	uint32_t mc_io_debug_edc_rx_dyn_pm_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rx_eq_d0 {
	uint32_t mc_io_debug_edc_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rx_eq_d1 {
	uint32_t mc_io_debug_edc_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rx_eq_pm_d0 {
	uint32_t mc_io_debug_edc_rx_eq_pm_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rx_eq_pm_d1 {
	uint32_t mc_io_debug_edc_rx_eq_pm_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rxphase_d0 {
	uint32_t mc_io_debug_edc_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rxphase_d1 {
	uint32_t mc_io_debug_edc_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rx_vref_cal_d0 {
	uint32_t mc_io_debug_edc_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_rx_vref_cal_d1 {
	uint32_t mc_io_debug_edc_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_txbst_pd_d0 {
	uint32_t mc_io_debug_edc_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_txbst_pd_d1 {
	uint32_t mc_io_debug_edc_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_txbst_pu_d0 {
	uint32_t mc_io_debug_edc_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_txbst_pu_d1 {
	uint32_t mc_io_debug_edc_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_txphase_d0 {
	uint32_t mc_io_debug_edc_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_txphase_d1 {
	uint32_t mc_io_debug_edc_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_txslf_d0 {
	uint32_t mc_io_debug_edc_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_edc_txslf_d1 {
	uint32_t mc_io_debug_edc_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_0 {
	uint32_t mc_io_debug_up_0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_100 {
	uint32_t mc_io_debug_up_100;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_101 {
	uint32_t mc_io_debug_up_101;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_102 {
	uint32_t mc_io_debug_up_102;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_103 {
	uint32_t mc_io_debug_up_103;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_104 {
	uint32_t mc_io_debug_up_104;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_105 {
	uint32_t mc_io_debug_up_105;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_106 {
	uint32_t mc_io_debug_up_106;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_107 {
	uint32_t mc_io_debug_up_107;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_108 {
	uint32_t mc_io_debug_up_108;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_109 {
	uint32_t mc_io_debug_up_109;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_10 {
	uint32_t mc_io_debug_up_10;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_110 {
	uint32_t mc_io_debug_up_110;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_111 {
	uint32_t mc_io_debug_up_111;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_112 {
	uint32_t mc_io_debug_up_112;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_113 {
	uint32_t mc_io_debug_up_113;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_114 {
	uint32_t mc_io_debug_up_114;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_115 {
	uint32_t mc_io_debug_up_115;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_116 {
	uint32_t mc_io_debug_up_116;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_117 {
	uint32_t mc_io_debug_up_117;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_118 {
	uint32_t mc_io_debug_up_118;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_119 {
	uint32_t mc_io_debug_up_119;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_11 {
	uint32_t mc_io_debug_up_11;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_120 {
	uint32_t mc_io_debug_up_120;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_121 {
	uint32_t mc_io_debug_up_121;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_122 {
	uint32_t mc_io_debug_up_122;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_123 {
	uint32_t mc_io_debug_up_123;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_124 {
	uint32_t mc_io_debug_up_124;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_125 {
	uint32_t mc_io_debug_up_125;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_126 {
	uint32_t mc_io_debug_up_126;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_127 {
	uint32_t mc_io_debug_up_127;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_128 {
	uint32_t mc_io_debug_up_128;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_129 {
	uint32_t mc_io_debug_up_129;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_12 {
	uint32_t mc_io_debug_up_12;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_130 {
	uint32_t mc_io_debug_up_130;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_131 {
	uint32_t mc_io_debug_up_131;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_132 {
	uint32_t mc_io_debug_up_132;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_133 {
	uint32_t mc_io_debug_up_133;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_134 {
	uint32_t mc_io_debug_up_134;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_135 {
	uint32_t mc_io_debug_up_135;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_136 {
	uint32_t mc_io_debug_up_136;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_137 {
	uint32_t mc_io_debug_up_137;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_138 {
	uint32_t mc_io_debug_up_138;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_139 {
	uint32_t mc_io_debug_up_139;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_13 {
	uint32_t mc_io_debug_up_13;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_140 {
	uint32_t mc_io_debug_up_140;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_141 {
	uint32_t mc_io_debug_up_141;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_142 {
	uint32_t mc_io_debug_up_142;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_143 {
	uint32_t mc_io_debug_up_143;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_144 {
	uint32_t mc_io_debug_up_144;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_145 {
	uint32_t mc_io_debug_up_145;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_146 {
	uint32_t mc_io_debug_up_146;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_147 {
	uint32_t mc_io_debug_up_147;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_148 {
	uint32_t mc_io_debug_up_148;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_149 {
	uint32_t mc_io_debug_up_149;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_14 {
	uint32_t mc_io_debug_up_14;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_150 {
	uint32_t mc_io_debug_up_150;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_151 {
	uint32_t mc_io_debug_up_151;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_152 {
	uint32_t mc_io_debug_up_152;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_153 {
	uint32_t mc_io_debug_up_153;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_154 {
	uint32_t mc_io_debug_up_154;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_155 {
	uint32_t mc_io_debug_up_155;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_156 {
	uint32_t mc_io_debug_up_156;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_157 {
	uint32_t mc_io_debug_up_157;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_158 {
	uint32_t mc_io_debug_up_158;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_159 {
	uint32_t mc_io_debug_up_159;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_15 {
	uint32_t mc_io_debug_up_15;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_16 {
	uint32_t mc_io_debug_up_16;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_17 {
	uint32_t mc_io_debug_up_17;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_18 {
	uint32_t mc_io_debug_up_18;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_19 {
	uint32_t mc_io_debug_up_19;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_1 {
	uint32_t mc_io_debug_up_1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_20 {
	uint32_t mc_io_debug_up_20;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_21 {
	uint32_t mc_io_debug_up_21;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_22 {
	uint32_t mc_io_debug_up_22;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_23 {
	uint32_t mc_io_debug_up_23;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_24 {
	uint32_t mc_io_debug_up_24;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_25 {
	uint32_t mc_io_debug_up_25;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_26 {
	uint32_t mc_io_debug_up_26;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_27 {
	uint32_t mc_io_debug_up_27;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_28 {
	uint32_t mc_io_debug_up_28;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_29 {
	uint32_t mc_io_debug_up_29;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_2 {
	uint32_t mc_io_debug_up_2;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_30 {
	uint32_t mc_io_debug_up_30;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_31 {
	uint32_t mc_io_debug_up_31;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_32 {
	uint32_t mc_io_debug_up_32;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_33 {
	uint32_t mc_io_debug_up_33;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_34 {
	uint32_t mc_io_debug_up_34;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_35 {
	uint32_t mc_io_debug_up_35;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_36 {
	uint32_t mc_io_debug_up_36;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_37 {
	uint32_t mc_io_debug_up_37;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_38 {
	uint32_t mc_io_debug_up_38;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_39 {
	uint32_t mc_io_debug_up_39;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_3 {
	uint32_t mc_io_debug_up_3;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_40 {
	uint32_t mc_io_debug_up_40;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_41 {
	uint32_t mc_io_debug_up_41;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_42 {
	uint32_t mc_io_debug_up_42;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_43 {
	uint32_t mc_io_debug_up_43;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_44 {
	uint32_t mc_io_debug_up_44;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_45 {
	uint32_t mc_io_debug_up_45;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_46 {
	uint32_t mc_io_debug_up_46;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_47 {
	uint32_t mc_io_debug_up_47;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_48 {
	uint32_t mc_io_debug_up_48;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_49 {
	uint32_t mc_io_debug_up_49;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_4 {
	uint32_t mc_io_debug_up_4;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_50 {
	uint32_t mc_io_debug_up_50;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_51 {
	uint32_t mc_io_debug_up_51;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_52 {
	uint32_t mc_io_debug_up_52;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_53 {
	uint32_t mc_io_debug_up_53;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_54 {
	uint32_t mc_io_debug_up_54;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_55 {
	uint32_t mc_io_debug_up_55;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_56 {
	uint32_t mc_io_debug_up_56;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_57 {
	uint32_t mc_io_debug_up_57;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_58 {
	uint32_t mc_io_debug_up_58;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_59 {
	uint32_t mc_io_debug_up_59;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_5 {
	uint32_t mc_io_debug_up_5;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_60 {
	uint32_t mc_io_debug_up_60;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_61 {
	uint32_t mc_io_debug_up_61;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_62 {
	uint32_t mc_io_debug_up_62;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_63 {
	uint32_t mc_io_debug_up_63;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_64 {
	uint32_t mc_io_debug_up_64;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_65 {
	uint32_t mc_io_debug_up_65;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_66 {
	uint32_t mc_io_debug_up_66;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_67 {
	uint32_t mc_io_debug_up_67;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_68 {
	uint32_t mc_io_debug_up_68;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_69 {
	uint32_t mc_io_debug_up_69;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_6 {
	uint32_t mc_io_debug_up_6;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_70 {
	uint32_t mc_io_debug_up_70;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_71 {
	uint32_t mc_io_debug_up_71;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_72 {
	uint32_t mc_io_debug_up_72;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_73 {
	uint32_t mc_io_debug_up_73;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_74 {
	uint32_t mc_io_debug_up_74;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_75 {
	uint32_t mc_io_debug_up_75;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_76 {
	uint32_t mc_io_debug_up_76;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_77 {
	uint32_t mc_io_debug_up_77;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_78 {
	uint32_t mc_io_debug_up_78;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_79 {
	uint32_t mc_io_debug_up_79;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_7 {
	uint32_t mc_io_debug_up_7;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_80 {
	uint32_t mc_io_debug_up_80;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_81 {
	uint32_t mc_io_debug_up_81;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_82 {
	uint32_t mc_io_debug_up_82;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_83 {
	uint32_t mc_io_debug_up_83;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_84 {
	uint32_t mc_io_debug_up_84;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_85 {
	uint32_t mc_io_debug_up_85;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_86 {
	uint32_t mc_io_debug_up_86;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_87 {
	uint32_t mc_io_debug_up_87;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_88 {
	uint32_t mc_io_debug_up_88;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_89 {
	uint32_t mc_io_debug_up_89;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_8 {
	uint32_t mc_io_debug_up_8;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_90 {
	uint32_t mc_io_debug_up_90;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_91 {
	uint32_t mc_io_debug_up_91;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_92 {
	uint32_t mc_io_debug_up_92;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_93 {
	uint32_t mc_io_debug_up_93;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_94 {
	uint32_t mc_io_debug_up_94;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_95 {
	uint32_t mc_io_debug_up_95;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_96 {
	uint32_t mc_io_debug_up_96;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_97 {
	uint32_t mc_io_debug_up_97;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_98 {
	uint32_t mc_io_debug_up_98;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_99 {
	uint32_t mc_io_debug_up_99;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_up_9 {
	uint32_t mc_io_debug_up_9;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_cdr_phsize_d0 {
	uint32_t mc_io_debug_wcdr_cdr_phsize_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_cdr_phsize_d1 {
	uint32_t mc_io_debug_wcdr_cdr_phsize_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_clksel_d0 {
	uint32_t mc_io_debug_wcdr_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_clksel_d1 {
	uint32_t mc_io_debug_wcdr_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_misc_d0 {
	uint32_t mc_io_debug_wcdr_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_misc_d1 {
	uint32_t mc_io_debug_wcdr_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_ofscal_d0 {
	uint32_t mc_io_debug_wcdr_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_ofscal_d1 {
	uint32_t mc_io_debug_wcdr_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rx_dyn_pm_d0 {
	uint32_t mc_io_debug_wcdr_rx_dyn_pm_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rx_dyn_pm_d1 {
	uint32_t mc_io_debug_wcdr_rx_dyn_pm_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rx_eq_d0 {
	uint32_t mc_io_debug_wcdr_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rx_eq_d1 {
	uint32_t mc_io_debug_wcdr_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rx_eq_pm_d0 {
	uint32_t mc_io_debug_wcdr_rx_eq_pm_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rx_eq_pm_d1 {
	uint32_t mc_io_debug_wcdr_rx_eq_pm_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rxphase_d0 {
	uint32_t mc_io_debug_wcdr_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rxphase_d1 {
	uint32_t mc_io_debug_wcdr_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rx_vref_cal_d0 {
	uint32_t mc_io_debug_wcdr_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_rx_vref_cal_d1 {
	uint32_t mc_io_debug_wcdr_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_txbst_pd_d0 {
	uint32_t mc_io_debug_wcdr_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_txbst_pd_d1 {
	uint32_t mc_io_debug_wcdr_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_txbst_pu_d0 {
	uint32_t mc_io_debug_wcdr_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_txbst_pu_d1 {
	uint32_t mc_io_debug_wcdr_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_txphase_d0 {
	uint32_t mc_io_debug_wcdr_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_txphase_d1 {
	uint32_t mc_io_debug_wcdr_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_txslf_d0 {
	uint32_t mc_io_debug_wcdr_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wcdr_txslf_d1 {
	uint32_t mc_io_debug_wcdr_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_clksel_d0 {
	uint32_t mc_io_debug_wck_clksel_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_clksel_d1 {
	uint32_t mc_io_debug_wck_clksel_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_misc_d0 {
	uint32_t mc_io_debug_wck_misc_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_misc_d1 {
	uint32_t mc_io_debug_wck_misc_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_ofscal_d0 {
	uint32_t mc_io_debug_wck_ofscal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_ofscal_d1 {
	uint32_t mc_io_debug_wck_ofscal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_rx_eq_d0 {
	uint32_t mc_io_debug_wck_rx_eq_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_rx_eq_d1 {
	uint32_t mc_io_debug_wck_rx_eq_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_rxphase_d0 {
	uint32_t mc_io_debug_wck_rxphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_rxphase_d1 {
	uint32_t mc_io_debug_wck_rxphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_rx_vref_cal_d0 {
	uint32_t mc_io_debug_wck_rx_vref_cal_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_rx_vref_cal_d1 {
	uint32_t mc_io_debug_wck_rx_vref_cal_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_txbst_pd_d0 {
	uint32_t mc_io_debug_wck_txbst_pd_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_txbst_pd_d1 {
	uint32_t mc_io_debug_wck_txbst_pd_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_txbst_pu_d0 {
	uint32_t mc_io_debug_wck_txbst_pu_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_txbst_pu_d1 {
	uint32_t mc_io_debug_wck_txbst_pu_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_txphase_d0 {
	uint32_t mc_io_debug_wck_txphase_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_txphase_d1 {
	uint32_t mc_io_debug_wck_txphase_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_txslf_d0 {
	uint32_t mc_io_debug_wck_txslf_d0;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_debug_wck_txslf_d1 {
	uint32_t mc_io_debug_wck_txslf_d1;
	struct { uint32_t
		value0 :7-0 +1,
		value1 :15-8 +1,
		value2 :23-16 +1,
		value3 :31-24 +1;
	};
};

union mc_io_dphy_str_cntl_d0 {
	uint32_t mc_io_dphy_str_cntl_d0;
	struct { uint32_t
		pstr_off_d :5-0 +1,
		nstr_off_d :11-6 +1,
		pstr_off_s :17-12 +1,
		nstr_off_s :23-18 +1,
		use_d_cal  :24-24 +1,
		use_s_cal  :25-25 +1,
		cal_sel    :27-26 +1,
		load_d_str :28-28 +1,
		load_s_str :29-29 +1,
		rsvd0      :31-30 +1;
	};
};

union mc_io_dphy_str_cntl_d1 {
	uint32_t mc_io_dphy_str_cntl_d1;
	struct { uint32_t
		pstr_off_d :5-0 +1,
		nstr_off_d :11-6 +1,
		pstr_off_s :17-12 +1,
		nstr_off_s :23-18 +1,
		use_d_cal  :24-24 +1,
		use_s_cal  :25-25 +1,
		cal_sel    :27-26 +1,
		load_d_str :28-28 +1,
		load_s_str :29-29 +1,
		rsvd0      :31-30 +1;
	};
};

union mc_io_pad_cntl {
	uint32_t mc_io_pad_cntl;
	struct { uint32_t
		atbsel    :23-20 +1,
		atben     :29-24 +1,
		atbsel_d1 :30-30 +1,
		atbsel_d0 :31-31 +1;
	};
};

union mc_io_pad_cntl_d0 {
	uint32_t mc_io_pad_cntl_d0;
	struct { uint32_t
		delay_clk_sync   :2-2 +1,
		delay_cmd_sync   :3-3 +1,
		delay_adr_sync   :4-4 +1,
		rsvd0            :6-5 +1,
		mem_fall_out_clk :7-7 +1,
		mem_fall_out_cmd :8-8 +1,
		mem_fall_out_adr :9-9 +1,
		force_en_rd_str  :10-10 +1,
		en_rd_str_dly    :11-11 +1,
		disable_cmd      :12-12 +1,
		disable_adr      :13-13 +1,
		vrefi_en         :14-14 +1,
		vrefi_sel        :19-15 +1,
		ck_auto_en       :20-20 +1,
		ck_delay_sel     :21-21 +1,
		ck_delay_n       :23-22 +1,
		ck_delay_p       :25-24 +1,
		rsvd1            :26-26 +1,
		txpwroff_cke     :27-27 +1,
		uni_str          :28-28 +1,
		diff_str         :29-29 +1,
		gddr_pwron       :30-30 +1,
		txpwroff_clk     :31-31 +1;
	};
};

union mc_io_pad_cntl_d1 {
	uint32_t mc_io_pad_cntl_d1;
	struct { uint32_t
		delay_data_sync   :0-0 +1,
		delay_str_sync    :1-1 +1,
		delay_clk_sync    :2-2 +1,
		delay_cmd_sync    :3-3 +1,
		delay_adr_sync    :4-4 +1,
		mem_fall_out_data :5-5 +1,
		mem_fall_out_str  :6-6 +1,
		mem_fall_out_clk  :7-7 +1,
		mem_fall_out_cmd  :8-8 +1,
		mem_fall_out_adr  :9-9 +1,
		force_en_rd_str   :10-10 +1,
		en_rd_str_dly     :11-11 +1,
		disable_cmd       :12-12 +1,
		disable_adr       :13-13 +1,
		vrefi_en          :14-14 +1,
		vrefi_sel         :19-15 +1,
		ck_auto_en        :20-20 +1,
		ck_delay_sel      :21-21 +1,
		ck_delay_n        :23-22 +1,
		ck_delay_p        :25-24 +1,
		rsvd0             :26-26 +1,
		txpwroff_cke      :27-27 +1,
		uni_str           :28-28 +1,
		diff_str          :29-29 +1,
		gddr_pwron        :30-30 +1,
		txpwroff_clk      :31-31 +1;
	};
};

union mc_io_pad_cntl {
	uint32_t mc_io_pad_cntl;
	struct { uint32_t
		mem_io_imp_min :7-0 +1,
		mem_io_imp_max :15-8 +1,
		txphase_gray   :16-16 +1,
		rxphase_gray   :17-17 +1,
		ovl_yclkon_d0  :18-18 +1,
		ovl_yclkon_d1  :19-19 +1,
		rsvd0          :31-20 +1;
	};
};

union mc_io_rxcntl1_dphy0_d0 {
	uint32_t mc_io_rxcntl1_dphy0_d0;
	struct { uint32_t
		vrefcal1_msb :3-0 +1,
		vrefcal2_msb :7-4 +1,
		vrefcal3     :15-8 +1,
		vrefsel2     :16-16 +1,
		vrefsel3     :17-17 +1,
		vrefpdnb_1   :18-18 +1,
		rsvd0        :24-19 +1,
		pmd_loopback :27-25 +1,
		dll_rsv      :31-28 +1;
	};
};

union mc_io_rxcntl1_dphy0_d1 {
	uint32_t mc_io_rxcntl1_dphy0_d1;
	struct { uint32_t
		vrefcal1_msb :3-0 +1,
		vrefcal2_msb :7-4 +1,
		vrefcal3     :15-8 +1,
		vrefsel2     :16-16 +1,
		vrefsel3     :17-17 +1,
		vrefpdnb_1   :18-18 +1,
		rsvd0        :24-19 +1,
		pmd_loopback :27-25 +1,
		dll_rsv      :31-28 +1;
	};
};

union mc_io_rxcntl1_dphy1_d0 {
	uint32_t mc_io_rxcntl1_dphy1_d0;
	struct { uint32_t
		vrefcal1_msb :3-0 +1,
		vrefcal2_msb :7-4 +1,
		vrefcal3     :15-8 +1,
		vrefsel2     :16-16 +1,
		vrefsel3     :17-17 +1,
		vrefpdnb_1   :18-18 +1,
		rsvd0        :24-19 +1,
		pmd_loopback :27-25 +1,
		dll_rsv      :31-28 +1;
	};
};

union mc_io_rxcntl1_dphy1_d1 {
	uint32_t mc_io_rxcntl1_dphy1_d1;
	struct { uint32_t
		vrefcal1_msb :3-0 +1,
		vrefcal2_msb :7-4 +1,
		vrefcal3     :15-8 +1,
		vrefsel2     :16-16 +1,
		vrefsel3     :17-17 +1,
		vrefpdnb_1   :18-18 +1,
		rsvd0        :24-19 +1,
		pmd_loopback :27-25 +1,
		dll_rsv      :31-28 +1;
	};
};

union mc_io_rxcntl_dphy0_d0 {
	uint32_t mc_io_rxcntl_dphy0_d0;
	struct { uint32_t
		rxbiassel    :1-0 +1,
		rcvsel       :2-2 +1,
		vrefpdnb     :3-3 +1,
		rxdpwron_dly :5-4 +1,
		rxpdnb       :6-6 +1,
		rxlp         :7-7 +1,
		vrefcal      :11-8 +1,
		vrefcal_str  :15-12 +1,
		vrefsel      :16-16 +1,
		rsvd0        :17-17 +1,
		rx_peaksel   :19-18 +1,
		dll_adj_b0   :22-20 +1,
		rsvd1        :23-23 +1,
		dll_adj_b1   :26-24 +1,
		rsvd2        :27-27 +1,
		dll_adj_m    :28-28 +1,
		refclk_pwron :29-29 +1,
		dll_bw_ctrl  :31-30 +1;
	};
};

union mc_io_rxcntl_dphy0_d1 {
	uint32_t mc_io_rxcntl_dphy0_d1;
	struct { uint32_t
		rxbiassel    :1-0 +1,
		rcvsel       :2-2 +1,
		vrefpdnb     :3-3 +1,
		rxdpwron_dly :5-4 +1,
		rxpdnb       :6-6 +1,
		rxlp         :7-7 +1,
		vrefcal      :11-8 +1,
		vrefcal_str  :15-12 +1,
		vrefsel      :16-16 +1,
		rsvd0        :17-17 +1,
		rx_peaksel   :19-18 +1,
		dll_adj_b0   :22-20 +1,
		rsvd1        :23-23 +1,
		dll_adj_b1   :26-24 +1,
		rsvd2        :27-27 +1,
		dll_adj_m    :28-28 +1,
		refclk_pwron :29-29 +1,
		dll_bw_ctrl  :31-30 +1;
	};
};

union mc_io_rxcntl_dphy1_d0 {
	uint32_t mc_io_rxcntl_dphy1_d0;
	struct { uint32_t
		rxbiassel    :1-0 +1,
		rcvsel       :2-2 +1,
		vrefpdnb     :3-3 +1,
		rxdpwron_dly :5-4 +1,
		rxpdnb       :6-6 +1,
		rxlp         :7-7 +1,
		vrefcal      :11-8 +1,
		vrefcal_str  :15-12 +1,
		vrefsel      :16-16 +1,
		rsvd0        :17-17 +1,
		rx_peaksel   :19-18 +1,
		dll_adj_b0   :22-20 +1,
		rsvd1        :23-23 +1,
		dll_adj_b1   :26-24 +1,
		rsvd2        :27-27 +1,
		dll_adj_m    :28-28 +1,
		refclk_pwron :29-29 +1,
		dll_bw_ctrl  :31-30 +1;
	};
};

union mc_io_rxcntl_dphy1_d1 {
	uint32_t mc_io_rxcntl_dphy1_d1;
	struct { uint32_t
		rxbiassel    :1-0 +1,
		rcvsel       :2-2 +1,
		vrefpdnb     :3-3 +1,
		rxdpwron_dly :5-4 +1,
		rxpdnb       :6-6 +1,
		rxlp         :7-7 +1,
		vrefcal      :11-8 +1,
		vrefcal_str  :15-12 +1,
		vrefsel      :16-16 +1,
		rsvd0        :17-17 +1,
		rx_peaksel   :19-18 +1,
		dll_adj_b0   :22-20 +1,
		rsvd1        :23-23 +1,
		dll_adj_b1   :26-24 +1,
		rsvd2        :27-27 +1,
		dll_adj_m    :28-28 +1,
		refclk_pwron :29-29 +1,
		dll_bw_ctrl  :31-30 +1;
	};
};

union mc_io_txcntl_aphy_d0 {
	uint32_t mc_io_txcntl_aphy_d0;
	struct { uint32_t
		biassel       :1-0 +1,
		drvduty       :3-2 +1,
		lowcmen       :4-4 +1,
		qdr           :5-5 +1,
		emph          :6-6 +1,
		txpd          :7-7 +1,
		pterm         :11-8 +1,
		txbpass_sel   :12-12 +1,
		pma_loopback  :15-13 +1,
		pdrv          :19-16 +1,
		ndrv          :22-20 +1,
		yclkon        :23-23 +1,
		tsten         :24-24 +1,
		txreset       :25-25 +1,
		txbypass      :26-26 +1,
		txbypass_data :29-27 +1,
		cke_bit       :30-30 +1,
		cke_sel       :31-31 +1;
	};
};

union mc_io_txcntl_aphy_d1 {
	uint32_t mc_io_txcntl_aphy_d1;
	struct { uint32_t
		biassel       :1-0 +1,
		drvduty       :3-2 +1,
		lowcmen       :4-4 +1,
		qdr           :5-5 +1,
		emph          :6-6 +1,
		txpd          :7-7 +1,
		pterm         :11-8 +1,
		txbpass_sel   :12-12 +1,
		pma_loopback  :15-13 +1,
		pdrv          :19-16 +1,
		ndrv          :22-20 +1,
		yclkon        :23-23 +1,
		tsten         :24-24 +1,
		txreset       :25-25 +1,
		txbypass      :26-26 +1,
		txbypass_data :29-27 +1,
		cke_bit       :30-30 +1,
		cke_sel       :31-31 +1;
	};
};

union mc_io_txcntl_dphy0_d0 {
	uint32_t mc_io_txcntl_dphy0_d0;
	struct { uint32_t
		biassel          :1-0 +1,
		drvduty          :3-2 +1,
		lowcmen          :4-4 +1,
		qdr              :5-5 +1,
		emph             :6-6 +1,
		txpd             :7-7 +1,
		pterm            :11-8 +1,
		nterm            :15-12 +1,
		pdrv             :19-16 +1,
		ndrv             :23-20 +1,
		tsten            :24-24 +1,
		edctx_clkgate_en :25-25 +1,
		txbypass         :26-26 +1,
		pll_loopbck      :27-27 +1,
		txbypass_data    :31-28 +1;
	};
};

union mc_io_txcntl_dphy0_d1 {
	uint32_t mc_io_txcntl_dphy0_d1;
	struct { uint32_t
		biassel          :1-0 +1,
		drvduty          :3-2 +1,
		lowcmen          :4-4 +1,
		qdr              :5-5 +1,
		emph             :6-6 +1,
		txpd             :7-7 +1,
		pterm            :11-8 +1,
		nterm            :15-12 +1,
		pdrv             :19-16 +1,
		ndrv             :23-20 +1,
		tsten            :24-24 +1,
		edctx_clkgate_en :25-25 +1,
		txbypass         :26-26 +1,
		pll_loopbck      :27-27 +1,
		txbypass_data    :31-28 +1;
	};
};

union mc_io_txcntl_dphy1_d0 {
	uint32_t mc_io_txcntl_dphy1_d0;
	struct { uint32_t
		biassel          :1-0 +1,
		drvduty          :3-2 +1,
		lowcmen          :4-4 +1,
		qdr              :5-5 +1,
		emph             :6-6 +1,
		txpd             :7-7 +1,
		pterm            :11-8 +1,
		nterm            :15-12 +1,
		pdrv             :19-16 +1,
		ndrv             :23-20 +1,
		tsten            :24-24 +1,
		edctx_clkgate_en :25-25 +1,
		txbypass         :26-26 +1,
		pll_loopbck      :27-27 +1,
		txbypass_data    :31-28 +1;
	};
};

union mc_io_txcntl_dphy1_d1 {
	uint32_t mc_io_txcntl_dphy1_d1;
	struct { uint32_t
		biassel          :1-0 +1,
		drvduty          :3-2 +1,
		lowcmen          :4-4 +1,
		qdr              :5-5 +1,
		emph             :6-6 +1,
		txpd             :7-7 +1,
		pterm            :11-8 +1,
		nterm            :15-12 +1,
		pdrv             :19-16 +1,
		ndrv             :23-20 +1,
		tsten            :24-24 +1,
		edctx_clkgate_en :25-25 +1,
		txbypass         :26-26 +1,
		pll_loopbck      :27-27 +1,
		txbypass_data    :31-28 +1;
	};
};

union mclk_pwrmgt_cntl {
	uint32_t mclk_pwrmgt_cntl;
	struct { uint32_t
		dll_speed      :4-0 +1,
		rsvd0          :5-5 +1,
		dll_ready      :6-6 +1,
		mc_int_cntl    :7-7 +1,
		mrdck0_pdnb    :8-8 +1,
		mrdck1_pdnb    :9-9 +1,
		rsvd1          :15-10 +1,
		mrdck0_reset   :16-16 +1,
		mrdck1_reset   :17-17 +1,
		rsvd2          :23-18 +1,
		dll_ready_read :24-24 +1,
		rsvd3          :31-25 +1;
	};
};

union mc_mem_power_ls {
	uint32_t mc_mem_power_ls;
	struct { uint32_t
		ls_setup :5-0 +1,
		ls_hold  :11-6 +1,
		rsvd0    :31-12 +1;
	};
};

union mc_npl_status {
	uint32_t mc_npl_status;
	struct { uint32_t
		d0_pdelay :1-0 +1,
		d0_ndelay :3-2 +1,
		d0_pearly :4-4 +1,
		d0_nearly :5-5 +1,
		d1_pdelay :7-6 +1,
		d1_ndelay :9-8 +1,
		d1_pearly :10-10 +1,
		d1_nearly :11-11 +1,
		rsvd0     :31-12 +1;
	};
};

union mc_phy_timing_2 {
	uint32_t mc_phy_timing_2;
	struct { uint32_t
		ind_ld_cnt   :6-0 +1,
		rsvd0        :7-7 +1,
		rxc0_inv     :8-8 +1,
		rxc1_inv     :9-9 +1,
		txc0_inv     :10-10 +1,
		txc1_inv     :11-11 +1,
		rxc0_frc     :12-12 +1,
		rxc1_frc     :13-13 +1,
		txc0_frc     :14-14 +1,
		txc1_frc     :15-15 +1,
		tx_cdren_d0  :16-16 +1,
		tx_cdren_d1  :17-17 +1,
		adr_clken_d0 :18-18 +1,
		adr_clken_d1 :19-19 +1,
		wr_dly       :23-20 +1,
		rsvd1        :31-24 +1;
	};
};

union mc_phy_timing_d0 {
	uint32_t mc_phy_timing_d0;
	struct { uint32_t
		rxc0_dly :3-0 +1,
		rxc0_ext :7-4 +1,
		rxc1_dly :11-8 +1,
		rxc1_ext :15-12 +1,
		txc0_dly :18-16 +1,
		rsvd0    :19-19 +1,
		txc0_ext :23-20 +1,
		txc1_dly :26-24 +1,
		rsvd1    :27-27 +1,
		txc1_ext :31-28 +1;
	};
};

union mc_phy_timing_d1 {
	uint32_t mc_phy_timing_d1;
	struct { uint32_t
		rxc0_dly :3-0 +1,
		rxc0_ext :7-4 +1,
		rxc1_dly :11-8 +1,
		rxc1_ext :15-12 +1,
		txc0_dly :18-16 +1,
		rsvd0    :19-19 +1,
		txc0_ext :23-20 +1,
		txc1_dly :26-24 +1,
		rsvd1    :27-27 +1,
		txc1_ext :31-28 +1;
	};
};

union mc_pmg_auto_cfg {
	uint32_t mc_pmg_auto_cfg;
	struct { uint32_t
		syc_clk            :0-0 +1,
		rst_mrs            :1-1 +1,
		tri_mio            :2-2 +1,
		rsvd0              :3-3 +1,
		xsr_tmr            :7-4 +1,
		ss_always_slf      :8-8 +1,
		ss_s_slf           :9-9 +1,
		scds_mode          :10-10 +1,
		exit_allow_stop    :11-11 +1,
		rfs_srx            :12-12 +1,
		prea_srx           :13-13 +1,
		stutter_en         :14-14 +1,
		selfrefr_commit_0  :15-15 +1,
		mrs_wait_cnt       :19-16 +1,
		write_during_dlock :20-20 +1,
		yclk_on            :21-21 +1,
		rxpdnb             :22-22 +1,
		selfrefr_commit_1  :23-23 +1,
		dll_cnt            :31-24 +1;
	};
};

union mc_pmg_auto_cmd {
	uint32_t mc_pmg_auto_cmd;
	struct { uint32_t
		adr      :16-0 +1,
		rsvd0    :27-17 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd1    :31-30 +1;
	};
};

union mc_pmg_cfg {
	uint32_t mc_pmg_cfg;
	struct { uint32_t
		syc_clk            :0-0 +1,
		rst_mrs            :1-1 +1,
		rst_emrs           :2-2 +1,
		tri_mio            :3-3 +1,
		xsr_tmr            :7-4 +1,
		rst_mrs1           :8-8 +1,
		rst_mrs2           :9-9 +1,
		dpm_wake           :10-10 +1,
		rsvd0              :11-11 +1,
		rfs_srx            :12-12 +1,
		prea_srx           :13-13 +1,
		rsvd1              :15-14 +1,
		mrs_wait_cnt       :19-16 +1,
		write_during_dlock :20-20 +1,
		yclk_on            :21-21 +1,
		early_ack_acpi     :22-22 +1,
		rsvd2              :24-23 +1,
		rxpdnb             :25-25 +1,
		zqcl_send          :27-26 +1,
		rsvd3              :31-28 +1;
	};
};

union mc_pmg_cmd_emrs {
	uint32_t mc_pmg_cmd_emrs;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :18-16 +1,
		bnk_msb  :19-19 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		rsvd0    :27-23 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd1    :31-30 +1;
	};
};

union mc_pmg_cmd_mrs1 {
	uint32_t mc_pmg_cmd_mrs1;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :18-16 +1,
		bnk_msb  :19-19 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		rsvd0    :27-23 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd1    :31-30 +1;
	};
};

union mc_pmg_cmd_mrs2 {
	uint32_t mc_pmg_cmd_mrs2;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :18-16 +1,
		bnk_msb  :19-19 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		rsvd0    :27-23 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd1    :31-30 +1;
	};
};

union mc_pmg_cmd_mrs {
	uint32_t mc_pmg_cmd_mrs;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :18-16 +1,
		bnk_msb  :19-19 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		rsvd0    :27-23 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd1    :31-30 +1;
	};
};

union mc_rd_cb {
	uint32_t mc_rd_cb;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_rd_db {
	uint32_t mc_rd_db;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_rd_grp_ext {
	uint32_t mc_rd_grp_ext;
	struct { uint32_t
		dbsten0 :3-0 +1,
		tc0     :7-4 +1,
		rsvd0   :31-8 +1;
	};
};

union mc_rd_grp_gfx {
	uint32_t mc_rd_grp_gfx;
	struct { uint32_t
		cp     :3-0 +1,
		rsvd0  :15-4 +1,
		xdmam  :19-16 +1,
		rsvd1  :31-20 +1;
	};
};

union mc_rd_grp_lcl {
	uint32_t mc_rd_grp_lcl;
	struct { uint32_t
		cb0      :15-12 +1,
		cbcmask0 :19-16 +1,
		cbfmask0 :23-20 +1,
		db0      :27-24 +1,
		dbhtile0 :31-28 +1;
	};
};

union mc_rd_grp_oth {
	uint32_t mc_rd_grp_oth;
	struct { uint32_t
		uvd_ext0 :3-0 +1,
		rsvd0    :7-4 +1,
		hdp      :11-8 +1,
		sem      :15-12 +1,
		umc      :19-16 +1,
		uvd      :23-20 +1,
		uvd_ext1 :27-24 +1,
		rsvd1    :31-28 +1;
	};
};

union mc_rd_grp_sys {
	uint32_t mc_rd_grp_sys;
	struct { uint32_t
		rlc    :3-0 +1,
		vmc    :7-4 +1,
		rsvd0  :11-8 +1,
		dmif   :15-12 +1,
		mcif   :19-16 +1,
		smu    :23-20 +1,
		vce    :27-24 +1,
		vceu   :31-28 +1;
	};
};

union mc_rd_hub {
	uint32_t mc_rd_hub;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_rd_tc0 {
	uint32_t mc_rd_tc0;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_rd_tc1 {
	uint32_t mc_rd_tc1;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_rpb_arb_cntl {
	uint32_t mc_rpb_arb_cntl;
	struct { uint32_t
		wr_switch_num  :7-0 +1,
		rd_switch_num  :15-8 +1,
		atc_switch_num :23-16 +1,
		rsvd0          :31-24 +1;
	};
};

union mc_rpb_bif_cntl {
	uint32_t mc_rpb_bif_cntl;
	struct { uint32_t
		arb_switch_num :7-0 +1,
		xpb_switch_num :15-8 +1,
		rsvd0          :31-16 +1;
	};
};

union mc_rpb_cid_queue_ex_data {
	uint32_t mc_rpb_cid_queue_ex_data;
	struct { uint32_t
		write_entries :15-0 +1,
		read_entries  :31-16 +1;
	};
};

union mc_rpb_cid_queue_ex {
	uint32_t mc_rpb_cid_queue_ex;
	struct { uint32_t
		start  :0-0 +1,
		offset :5-1 +1,
		rsvd0  :31-6 +1;
	};
};

union mc_rpb_cid_queue_rd {
	uint32_t mc_rpb_cid_queue_rd;
	struct { uint32_t
		client_id   :7-0 +1,
		write_queue :9-8 +1,
		read_queue  :11-10 +1,
		rsvd0       :31-12 +1;
	};
};

union mc_rpb_cid_queue_wr {
	uint32_t mc_rpb_cid_queue_wr;
	struct { uint32_t
		client_id   :7-0 +1,
		update_mode :8-8 +1,
		write_queue :10-9 +1,
		read_queue  :12-11 +1,
		update      :13-13 +1,
		rsvd0       :31-14 +1;
	};
};

union mc_rpb_conf {
	uint32_t mc_rpb_conf;
	struct { uint32_t
		xpb_pcie_order    :15-15 +1,
		rpb_rd_pcie_order :16-16 +1,
		rpb_wr_pcie_order :17-17 +1,
		rsvd0             :31-18 +1;
	};
};

union mc_rpb_dbg1 {
	uint32_t mc_rpb_dbg1;
	struct { uint32_t
		rpb_bif_outstanding_rd     :7-0 +1,
		rpb_bif_outstanding_rd_32b :19-8 +1,
		debug_bits                 :31-20 +1;
	};
};

union mc_rpb_eff_cntl {
	uint32_t mc_rpb_eff_cntl;
	struct { uint32_t
		wr_lazy_timer :7-0 +1,
		rd_lazy_timer :15-8 +1,
		rsvd0         :31-16 +1;
	};
};

union mc_rpb_if_conf {
	uint32_t mc_rpb_if_conf;
	struct { uint32_t
		rpb_bif_credits       :7-0 +1,
		outstanding_wrret_ask :15-8 +1,
		rsvd0                 :31-16 +1;
	};
};

union mc_rpb_perf_counter_cntl {
	uint32_t mc_rpb_perf_counter_cntl;
	struct { uint32_t
		perf_counter_select         :1-0 +1,
		clear_selected_perf_counter :2-2 +1,
		clear_all_perf_counters     :3-3 +1,
		stop_on_counter_saturation  :4-4 +1,
		enable_perf_counters        :8-5 +1,
		perf_counter_assign_0       :13-9 +1,
		perf_counter_assign_1       :18-14 +1,
		perf_counter_assign_2       :23-19 +1,
		perf_counter_assign_3       :28-24 +1,
		rsvd0                       :31-29 +1;
	};
};

union mc_rpb_perf_counter_status {
	uint32_t mc_rpb_perf_counter_status;
	struct { uint32_t
		performance_counter_value :31-0 +1;
	};
};

union mc_rpb_rd_switch_cntl {
	uint32_t mc_rpb_rd_switch_cntl;
	struct { uint32_t
		queue0_switch_num :7-0 +1,
		queue1_switch_num :15-8 +1,
		queue2_switch_num :23-16 +1,
		queue3_switch_num :31-24 +1;
	};
};

union mc_rpb_wr_combine_cntl {
	uint32_t mc_rpb_wr_combine_cntl;
	struct { uint32_t
		wc_enable          :0-0 +1,
		wc_max_packet_size :2-1 +1,
		wc_flush_timer     :6-3 +1,
		wc_align           :7-7 +1,
		rsvd0              :31-8 +1;
	};
};

union mc_rpb_wr_switch_cntl {
	uint32_t mc_rpb_wr_switch_cntl;
	struct { uint32_t
		queue0_switch_num :7-0 +1,
		queue1_switch_num :15-8 +1,
		queue2_switch_num :23-16 +1,
		queue3_switch_num :31-24 +1;
	};
};

union mc_seq_bit_remap_b0_d0 {
	uint32_t mc_seq_bit_remap_b0_d0;
	struct { uint32_t
		bit0   :2-0 +1,
		bit1   :5-3 +1,
		bit2   :8-6 +1,
		bit3   :11-9 +1,
		bit4   :14-12 +1,
		bit5   :17-15 +1,
		bit6   :20-18 +1,
		bit7   :23-21 +1,
		rsvd0  :31-24 +1;
	};
};

union mc_seq_bit_remap_b0_d1 {
	uint32_t mc_seq_bit_remap_b0_d1;
	struct { uint32_t
		bit0   :2-0 +1,
		bit1   :5-3 +1,
		bit2   :8-6 +1,
		bit3   :11-9 +1,
		bit4   :14-12 +1,
		bit5   :17-15 +1,
		bit6   :20-18 +1,
		bit7   :23-21 +1,
		rsvd0  :31-24 +1;
	};
};

union mc_seq_bit_remap_b1_d0 {
	uint32_t mc_seq_bit_remap_b1_d0;
	struct { uint32_t
		bit0   :2-0 +1,
		bit1   :5-3 +1,
		bit2   :8-6 +1,
		bit3   :11-9 +1,
		bit4   :14-12 +1,
		bit5   :17-15 +1,
		bit6   :20-18 +1,
		bit7   :23-21 +1,
		rsvd0  :31-24 +1;
	};
};

union mc_seq_bit_remap_b1_d1 {
	uint32_t mc_seq_bit_remap_b1_d1;
	struct { uint32_t
		bit0   :2-0 +1,
		bit1   :5-3 +1,
		bit2   :8-6 +1,
		bit3   :11-9 +1,
		bit4   :14-12 +1,
		bit5   :17-15 +1,
		bit6   :20-18 +1,
		bit7   :23-21 +1,
		rsvd0  :31-24 +1;
	};
};

union mc_seq_bit_remap_b2_d0 {
	uint32_t mc_seq_bit_remap_b2_d0;
	struct { uint32_t
		bit0   :2-0 +1,
		bit1   :5-3 +1,
		bit2   :8-6 +1,
		bit3   :11-9 +1,
		bit4   :14-12 +1,
		bit5   :17-15 +1,
		bit6   :20-18 +1,
		bit7   :23-21 +1,
		rsvd0  :31-24 +1;
	};
};

union mc_seq_bit_remap_b2_d1 {
	uint32_t mc_seq_bit_remap_b2_d1;
	struct { uint32_t
		bit0   :2-0 +1,
		bit1   :5-3 +1,
		bit2   :8-6 +1,
		bit3   :11-9 +1,
		bit4   :14-12 +1,
		bit5   :17-15 +1,
		bit6   :20-18 +1,
		bit7   :23-21 +1,
		rsvd0  :31-24 +1;
	};
};

union mc_seq_bit_remap_b3_d0 {
	uint32_t mc_seq_bit_remap_b3_d0;
	struct { uint32_t
		bit0   :2-0 +1,
		bit1   :5-3 +1,
		bit2   :8-6 +1,
		bit3   :11-9 +1,
		bit4   :14-12 +1,
		bit5   :17-15 +1,
		bit6   :20-18 +1,
		bit7   :23-21 +1,
		rsvd0  :31-24 +1;
	};
};

union mc_seq_bit_remap_b3_d1 {
	uint32_t mc_seq_bit_remap_b3_d1;
	struct { uint32_t
		bit0   :2-0 +1,
		bit1   :5-3 +1,
		bit2   :8-6 +1,
		bit3   :11-9 +1,
		bit4   :14-12 +1,
		bit5   :17-15 +1,
		bit6   :20-18 +1,
		bit7   :23-21 +1,
		rsvd0  :31-24 +1;
	};
};

union mc_seq_byte_remap_d0 {
	uint32_t mc_seq_byte_remap_d0;
	struct { uint32_t
		byte0  :1-0 +1,
		byte1  :3-2 +1,
		byte2  :5-4 +1,
		byte3  :7-6 +1,
		rsvd0  :31-8 +1;
	};
};

union mc_seq_byte_remap_d1 {
	uint32_t mc_seq_byte_remap_d1;
	struct { uint32_t
		byte0  :1-0 +1,
		byte1  :3-2 +1,
		byte2  :5-4 +1,
		byte3  :7-6 +1,
		rsvd0  :31-8 +1;
	};
};

union mc_seq_cas_timing_lp {
	uint32_t mc_seq_cas_timing_lp;
	struct { uint32_t
		tnopw  :1-0 +1,
		tnopr  :3-2 +1,
		tr2w   :8-4 +1,
		tccdl  :11-9 +1,
		tr2r   :15-12 +1,
		tw2r   :20-16 +1,
		rsvd0  :23-21 +1,
		tcl    :28-24 +1,
		rsvd1  :31-29 +1;
	};
};

union mc_seq_cas_timing {
	uint32_t mc_seq_cas_timing;
	struct { uint32_t
		tnopw  :1-0 +1,
		tnopr  :3-2 +1,
		tr2w   :8-4 +1,
		tccdl  :11-9 +1,
		tr2r   :15-12 +1,
		tw2r   :20-16 +1,
		rsvd0  :23-21 +1,
		tcl    :28-24 +1,
		rsvd1  :31-29 +1;
	};
};

union mc_seq_cg {
	uint32_t mc_seq_cg;
	struct { uint32_t
		cg_seq_req  :7-0 +1,
		cg_seq_resp :15-8 +1,
		seq_cg_req  :23-16 +1,
		seq_cg_resp :31-24 +1;
	};
};

union mc_seq_cmd {
	uint32_t mc_seq_cmd;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :19-16 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		rsvd0    :23-23 +1,
		chan0    :24-24 +1,
		chan1    :25-25 +1,
		rsvd1    :27-26 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd2    :31-30 +1;
	};
};

union mc_seq_cntl_2 {
	uint32_t mc_seq_cntl_2;
	struct { uint32_t
		arb_rtdat_wmk_msb :9-8 +1,
		drst_nstr         :15-10 +1,
		drst_pstr         :21-16 +1,
		pll_tx_pwron_d0   :22-22 +1,
		pll_tx_pwron_d1   :23-23 +1,
		pll_rx_pwron_d0   :27-24 +1,
		pll_rx_pwron_d1   :31-28 +1;
	};
};

union mc_seq_cntl {
	uint32_t mc_seq_cntl;
	struct { uint32_t
		mem_addr_map_cols :1-0 +1,
		mem_addr_map_bank :3-2 +1,
		safe_mode         :5-4 +1,
		dat_inv           :6-6 +1,
		msk_df1           :7-7 +1,
		channel_disable   :9-8 +1,
		rsvd0             :13-10 +1,
		mskoff_dat_tl     :14-14 +1,
		mskoff_dat_th     :15-15 +1,
		ret_hold_eop      :16-16 +1,
		bankgroup_size    :17-17 +1,
		bankgroup_enb     :18-18 +1,
		rtr_override      :19-19 +1,
		arb_reqcmd_wmk    :23-20 +1,
		arb_reqdat_wmk    :27-24 +1,
		arb_rtdat_wmk     :31-28 +1;
	};
};

union mc_seq_dram_2 {
	uint32_t mc_seq_dram_2;
	struct { uint32_t
		adr_ddr     :0-0 +1,
		adr_dbi     :1-1 +1,
		adr_dbi_acm :2-2 +1,
		cmd_qdr     :3-3 +1,
		dat_qdr     :4-4 +1,
		wdat_edc    :5-5 +1,
		rdat_edc    :6-6 +1,
		dqm_est     :7-7 +1,
		rd_dqs      :8-8 +1,
		wr_dqs      :9-9 +1,
		pll_est     :10-10 +1,
		pll_clr     :11-11 +1,
		dll_est     :12-12 +1,
		bnk_mrs     :13-13 +1,
		dbi_ovr     :14-14 +1,
		tri_clk     :15-15 +1,
		pll_cnt     :23-16 +1,
		pch_bnk     :24-24 +1,
		adbi_df1    :25-25 +1,
		adbi_act    :26-26 +1,
		dbi_df1     :27-27 +1,
		dbi_act     :28-28 +1,
		dbi_edc_df1 :29-29 +1,
		testchip_en :30-30 +1,
		cs_by16     :31-31 +1;
	};
};

union mc_seq_dram {
	uint32_t mc_seq_dram;
	struct { uint32_t
		adr_2ck :0-0 +1,
		adr_mux :1-1 +1,
		adr_df1 :2-2 +1,
		ap8     :3-3 +1,
		dat_df1 :4-4 +1,
		dqs_df1 :5-5 +1,
		dqm_df1 :6-6 +1,
		dqm_act :7-7 +1,
		rsvd0   :11-8 +1,
		cke_dyn :12-12 +1,
		cke_act :13-13 +1,
		bo4     :14-14 +1,
		dll_clr :15-15 +1,
		dll_cnt :23-16 +1,
		dat_inv :24-24 +1,
		rsvd1   :31-25 +1;
	};
};

union mc_seq_dram_error_insertion {
	uint32_t mc_seq_dram_error_insertion;
	struct { uint32_t
		tx     :15-0 +1,
		rx     :31-16 +1;
	};
};

union mc_seq_dram {
	uint32_t mc_seq_dram;
	struct { uint32_t
		stb_cnt     :11-8 +1,
		rsvd0       :24-12 +1,
		inv_acm     :25-25 +1,
		odt_enb     :26-26 +1,
		odt_act     :27-27 +1,
		rst_ctl     :28-28 +1,
		tri_mio_dyn :29-29 +1,
		tri_cke     :30-30 +1,
		rsvd1       :31-31 +1;
	};
};

union mc_seq_fifo_ctl {
	uint32_t mc_seq_fifo_ctl;
	struct { uint32_t
		w_ld_init_d0 :1-0 +1,
		w_syc_sel    :3-2 +1,
		r_ld_init    :5-4 +1,
		r_syc_sel    :7-6 +1,
		cg_dis_d0    :8-8 +1,
		cg_dis_d1    :9-9 +1,
		w_ld_init_d1 :11-10 +1,
		syc_dly      :14-12 +1,
		rsvd0        :15-15 +1,
		w_asyc_ext   :17-16 +1,
		w_dsyc_ext   :19-18 +1,
		rsvd1        :31-20 +1;
	};
};

union mc_seq_io_debug_data {
	uint32_t mc_seq_io_debug_data;
	struct { uint32_t
		io_debug_data :31-0 +1;
	};
};

union mc_seq_io_debug_index {
	uint32_t mc_seq_io_debug_index;
	struct { uint32_t
		io_debug_index :8-0 +1,
		rsvd0          :31-9 +1;
	};
};

union mc_seq_io_rdbi {
	uint32_t mc_seq_io_rdbi;
	struct { uint32_t
		mask   :31-0 +1;
	};
};

union mc_seq_io_redc {
	uint32_t mc_seq_io_redc;
	struct { uint32_t
		edc    :31-0 +1;
	};
};

union mc_seq_io_reserve_d0 {
	uint32_t mc_seq_io_reserve_d0;
	struct { uint32_t
		dphy0_rsv :11-0 +1,
		dphy1_rsv :23-12 +1,
		aphy_rsv  :31-24 +1;
	};
};

union mc_seq_io_reserve_d1 {
	uint32_t mc_seq_io_reserve_d1;
	struct { uint32_t
		dphy0_rsv :11-0 +1,
		dphy1_rsv :23-12 +1,
		aphy_rsv  :31-24 +1;
	};
};

union mc_seq_io_rword0 {
	uint32_t mc_seq_io_rword0;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_seq_io_rword1 {
	uint32_t mc_seq_io_rword1;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_seq_io_rword2 {
	uint32_t mc_seq_io_rword2;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_seq_io_rword3 {
	uint32_t mc_seq_io_rword3;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_seq_io_rword4 {
	uint32_t mc_seq_io_rword4;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_seq_io_rword5 {
	uint32_t mc_seq_io_rword5;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_seq_io_rword6 {
	uint32_t mc_seq_io_rword6;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_seq_io_rword7 {
	uint32_t mc_seq_io_rword7;
	struct { uint32_t
		rdata  :31-0 +1;
	};
};

union mc_seq_misc0 {
	uint32_t mc_seq_misc0;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_misc1 {
	uint32_t mc_seq_misc1;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_misc3 {
	uint32_t mc_seq_misc3;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_misc4 {
	uint32_t mc_seq_misc4;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_misc5 {
	uint32_t mc_seq_misc5;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_misc6 {
	uint32_t mc_seq_misc6;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_misc7 {
	uint32_t mc_seq_misc7;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_misc8 {
	uint32_t mc_seq_misc8;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_misc9 {
	uint32_t mc_seq_misc9;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_misc_timing2 {
	uint32_t mc_seq_misc_timing2;
	struct { uint32_t
		faw    :12-8 +1,
		rsvd0  :31-13 +1;
	};
};

union mc_seq_misc_timing2_lp {
	uint32_t mc_seq_misc_timing2_lp;
	struct { uint32_t
		pa2rdata :2-0 +1,
		rsvd0    :3-3 +1,
		pa2wdata :6-4 +1,
		rsvd1    :7-7 +1,
		faw      :12-8 +1,
		tredc    :15-13 +1,
		twedc    :20-16 +1,
		tadr     :23-21 +1,
		tfcktr   :27-24 +1,
		twdatatr :31-28 +1;
	};
};

union mc_seq_misc_timing2 {
	uint32_t mc_seq_misc_timing2;
	struct { uint32_t
		pa2rdata :2-0 +1,
		rsvd0    :3-3 +1,
		pa2wdata :6-4 +1,
		rsvd1    :12-7 +1,
		tredc    :15-13 +1,
		twedc    :20-16 +1,
		t32aw    :24-21 +1,
		rsvd2    :27-25 +1,
		twdatatr :31-28 +1;
	};
};

union mc_seq_misc_timing_lp {
	uint32_t mc_seq_misc_timing_lp;
	struct { uint32_t
		trp_wra :5-0 +1,
		rsvd0   :7-6 +1,
		trp_rda :13-8 +1,
		rsvd1   :14-14 +1,
		trp     :19-15 +1,
		trfc    :28-20 +1,
		rsvd2   :31-29 +1;
	};
};

union mc_seq_misc_timing {
	uint32_t mc_seq_misc_timing;
	struct { uint32_t
		trp_wra :5-0 +1,
		rsvd0   :7-6 +1,
		trp_rda :13-8 +1,
		rsvd1   :14-14 +1,
		trp     :19-15 +1,
		trfc    :28-20 +1,
		rsvd2   :31-29 +1;
	};
};

union mc_seq_mpll_override {
	uint32_t mc_seq_mpll_override;
	struct { uint32_t
		ad_pll_reset_override        :0-0 +1,
		dq_0_0_pll_reset_override    :1-1 +1,
		dq_0_1_pll_reset_override    :2-2 +1,
		dq_1_0_pll_reset_override    :3-3 +1,
		dq_1_1_pll_reset_override    :4-4 +1,
		atgm_clk_sel_override        :5-5 +1,
		test_bypass_clk_en_override  :6-6 +1,
		test_bypass_clk_sel_override :7-7 +1,
		rsvd0                        :31-8 +1;
	};
};

union mc_seq_perf_cntl_1 {
	uint32_t mc_seq_perf_cntl_1;
	struct { uint32_t
		pause         :0-0 +1,
		rsvd0         :7-1 +1,
		sel_a_msb     :8-8 +1,
		sel_b_msb     :9-9 +1,
		sel_ch0_c_msb :10-10 +1,
		sel_ch0_d_msb :11-11 +1,
		sel_ch1_a_msb :12-12 +1,
		sel_ch1_b_msb :13-13 +1,
		sel_ch1_c_msb :14-14 +1,
		sel_ch1_d_msb :15-15 +1,
		rsvd1         :31-16 +1;
	};
};

union mc_seq_perf_cntl {
	uint32_t mc_seq_perf_cntl;
	struct { uint32_t
		monitor_period :29-0 +1,
		cntl           :31-30 +1;
	};
};

union mc_seq_perf_seq_cnt_a_i0 {
	uint32_t mc_seq_perf_seq_cnt_a_i0;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_perf_seq_cnt_a_i1 {
	uint32_t mc_seq_perf_seq_cnt_a_i1;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_perf_seq_cnt_b_i0 {
	uint32_t mc_seq_perf_seq_cnt_b_i0;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_perf_seq_cnt_b_i1 {
	uint32_t mc_seq_perf_seq_cnt_b_i1;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_perf_seq_cnt_c_i0 {
	uint32_t mc_seq_perf_seq_cnt_c_i0;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_perf_seq_cnt_c_i1 {
	uint32_t mc_seq_perf_seq_cnt_c_i1;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_perf_seq_cnt_d_i0 {
	uint32_t mc_seq_perf_seq_cnt_d_i0;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_perf_seq_cnt_d_i1 {
	uint32_t mc_seq_perf_seq_cnt_d_i1;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_perf_seq_ctl {
	uint32_t mc_seq_perf_seq_ctl;
	struct { uint32_t
		sel_a     :3-0 +1,
		sel_b     :7-4 +1,
		sel_ch0_c :11-8 +1,
		sel_ch0_d :15-12 +1,
		sel_ch1_a :19-16 +1,
		sel_ch1_b :23-20 +1,
		sel_ch1_c :27-24 +1,
		sel_ch1_d :31-28 +1;
	};
};

union mc_seq_pmg_cmd_emrs_lp {
	uint32_t mc_seq_pmg_cmd_emrs_lp;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :18-16 +1,
		bnk_msb  :19-19 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		rsvd0    :27-23 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd1    :31-30 +1;
	};
};

union mc_seq_pmg_cmd_mrs1_lp {
	uint32_t mc_seq_pmg_cmd_mrs1_lp;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :18-16 +1,
		bnk_msb  :19-19 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		rsvd0    :27-23 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd1    :31-30 +1;
	};
};

union mc_seq_pmg_cmd_mrs2_lp {
	uint32_t mc_seq_pmg_cmd_mrs2_lp;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :18-16 +1,
		bnk_msb  :19-19 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		rsvd0    :27-23 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd1    :31-30 +1;
	};
};

union mc_seq_pmg_cmd_mrs_lp {
	uint32_t mc_seq_pmg_cmd_mrs_lp;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :18-16 +1,
		bnk_msb  :19-19 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		rsvd0    :27-23 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		rsvd1    :31-30 +1;
	};
};

union mc_seq_pmg_pg_hwcntl {
	uint32_t mc_seq_pmg_pg_hwcntl;
	struct { uint32_t
		pwrgate_en :0-0 +1,
		stagger_en :1-1 +1,
		tpgcg      :5-2 +1,
		d_dly      :7-6 +1,
		ac_dly     :9-8 +1,
		g_dly      :13-10 +1,
		rsvd0      :15-14 +1,
		txao       :16-16 +1,
		rxao       :17-17 +1,
		acao       :18-18 +1,
		rsvd1      :31-19 +1;
	};
};

union mc_seq_pmg_pg_swcntl_0 {
	uint32_t mc_seq_pmg_pg_swcntl_0;
	struct { uint32_t
		pmd0_dq_tx_enb    :0-0 +1,
		pmd0_dbi_tx_enb   :1-1 +1,
		pmd0_edc_tx_enb   :2-2 +1,
		pmd0_wclkx_tx_enb :3-3 +1,
		pmd0_dq_rx_enb    :4-4 +1,
		pmd0_dbi_rx_enb   :5-5 +1,
		pmd0_edc_rx_enb   :6-6 +1,
		pmd0_wclkx_rx_enb :7-7 +1,
		pmd1_dq_tx_enb    :8-8 +1,
		pmd1_dbi_tx_enb   :9-9 +1,
		pmd1_edc_tx_enb   :10-10 +1,
		pmd1_wclkx_tx_enb :11-11 +1,
		pmd1_dq_rx_enb    :12-12 +1,
		pmd1_dbi_rx_enb   :13-13 +1,
		pmd1_edc_rx_enb   :14-14 +1,
		pmd1_wclkx_rx_enb :15-15 +1,
		pma0_ac_enb       :16-16 +1,
		rsvd0             :30-17 +1,
		gmcon_sr_commit   :31-31 +1;
	};
};

union mc_seq_pmg_pg_swcntl_1 {
	uint32_t mc_seq_pmg_pg_swcntl_1;
	struct { uint32_t
		pmd2_dq_tx_enb    :0-0 +1,
		pmd2_dbi_tx_enb   :1-1 +1,
		pmd2_edc_tx_enb   :2-2 +1,
		pmd2_wclkx_tx_enb :3-3 +1,
		pmd2_dq_rx_enb    :4-4 +1,
		pmd2_dbi_rx_enb   :5-5 +1,
		pmd2_edc_rx_enb   :6-6 +1,
		pmd2_wclkx_rx_enb :7-7 +1,
		pmd3_dq_tx_enb    :8-8 +1,
		pmd3_dbi_tx_enb   :9-9 +1,
		pmd3_edc_tx_enb   :10-10 +1,
		pmd3_wclkx_tx_enb :11-11 +1,
		pmd3_dq_rx_enb    :12-12 +1,
		pmd3_dbi_rx_enb   :13-13 +1,
		pmd3_edc_rx_enb   :14-14 +1,
		pmd3_wclkx_rx_enb :15-15 +1,
		pma1_ac_enb       :16-16 +1,
		rsvd0             :30-17 +1,
		gmcon_sr_commit   :31-31 +1;
	};
};

union mc_seq_pmg_timing_lp {
	uint32_t mc_seq_pmg_timing_lp;
	struct { uint32_t
		tcksre         :2-0 +1,
		rsvd0          :3-3 +1,
		tcksrx         :6-4 +1,
		rsvd1          :7-7 +1,
		tcke_pulse     :11-8 +1,
		tcke           :17-12 +1,
		seq_idle       :20-18 +1,
		rsvd2          :22-21 +1,
		tcke_pulse_msb :23-23 +1,
		seq_idle_ss    :31-24 +1;
	};
};

union mc_seq_pmg_timing {
	uint32_t mc_seq_pmg_timing;
	struct { uint32_t
		tcksre         :2-0 +1,
		rsvd0          :3-3 +1,
		tcksrx         :6-4 +1,
		rsvd1          :7-7 +1,
		tcke_pulse     :11-8 +1,
		tcke           :17-12 +1,
		seq_idle       :20-18 +1,
		rsvd2          :22-21 +1,
		tcke_pulse_msb :23-23 +1,
		seq_idle_ss    :31-24 +1;
	};
};

union mc_seq_ras_timing_lp {
	uint32_t mc_seq_ras_timing_lp;
	struct { uint32_t
		trcdw  :4-0 +1,
		trcdwa :9-5 +1,
		trcdr  :14-10 +1,
		trcdra :19-15 +1,
		trrd   :23-20 +1,
		trc    :30-24 +1,
		rsvd0  :31-31 +1;
	};
};

union mc_seq_ras_timing {
	uint32_t mc_seq_ras_timing;
	struct { uint32_t
		trcdw  :4-0 +1,
		trcdwa :9-5 +1,
		trcdr  :14-10 +1,
		trcdra :19-15 +1,
		trrd   :23-20 +1,
		trc    :30-24 +1,
		rsvd0  :31-31 +1;
	};
};

union mc_seq_rd_ctl_d0_lp {
	uint32_t mc_seq_rd_ctl_d0_lp;
	struct { uint32_t
		rcv_dly      :2-0 +1,
		rcv_ext      :7-3 +1,
		rst_sel      :9-8 +1,
		rxdpwron_dly :11-10 +1,
		rst_hld      :15-12 +1,
		str_pre      :16-16 +1,
		str_pst      :17-17 +1,
		rsvd0        :19-18 +1,
		rbs_dly      :24-20 +1,
		rbs_wedc_dly :29-25 +1,
		rsvd1        :31-30 +1;
	};
};

union mc_seq_rd_ctl_d0 {
	uint32_t mc_seq_rd_ctl_d0;
	struct { uint32_t
		rcv_dly      :2-0 +1,
		rcv_ext      :7-3 +1,
		rst_sel      :9-8 +1,
		rxdpwron_dly :11-10 +1,
		rst_hld      :15-12 +1,
		str_pre      :16-16 +1,
		str_pst      :17-17 +1,
		rsvd0        :19-18 +1,
		rbs_dly      :24-20 +1,
		rbs_wedc_dly :29-25 +1,
		rsvd1        :31-30 +1;
	};
};

union mc_seq_rd_ctl_d1_lp {
	uint32_t mc_seq_rd_ctl_d1_lp;
	struct { uint32_t
		rcv_dly      :2-0 +1,
		rcv_ext      :7-3 +1,
		rst_sel      :9-8 +1,
		rxdpwron_dly :11-10 +1,
		rst_hld      :15-12 +1,
		str_pre      :16-16 +1,
		str_pst      :17-17 +1,
		rsvd0        :19-18 +1,
		rbs_dly      :24-20 +1,
		rbs_wedc_dly :29-25 +1,
		rsvd1        :31-30 +1;
	};
};

union mc_seq_rd_ctl_d1 {
	uint32_t mc_seq_rd_ctl_d1;
	struct { uint32_t
		rcv_dly      :2-0 +1,
		rcv_ext      :7-3 +1,
		rst_sel      :9-8 +1,
		rxdpwron_dly :11-10 +1,
		rst_hld      :15-12 +1,
		str_pre      :16-16 +1,
		str_pst      :17-17 +1,
		rsvd0        :19-18 +1,
		rbs_dly      :24-20 +1,
		rbs_wedc_dly :29-25 +1,
		rsvd1        :31-30 +1;
	};
};

union mc_seq_reserve_0_s {
	uint32_t mc_seq_reserve_0_s;
	struct { uint32_t
		sclk_field :31-0 +1;
	};
};

union mc_seq_reserve_1_s {
	uint32_t mc_seq_reserve_1_s;
	struct { uint32_t
		sclk_field :31-0 +1;
	};
};

union mc_seq_reserve_m {
	uint32_t mc_seq_reserve_m;
	struct { uint32_t
		mclk_field :31-0 +1;
	};
};

union mc_seq_rxframing_byte0_d0 {
	uint32_t mc_seq_rxframing_byte0_d0;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_rxframing_byte0_d1 {
	uint32_t mc_seq_rxframing_byte0_d1;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_rxframing_byte1_d0 {
	uint32_t mc_seq_rxframing_byte1_d0;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_rxframing_byte1_d1 {
	uint32_t mc_seq_rxframing_byte1_d1;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_rxframing_byte2_d0 {
	uint32_t mc_seq_rxframing_byte2_d0;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_rxframing_byte2_d1 {
	uint32_t mc_seq_rxframing_byte2_d1;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_rxframing_byte3_d0 {
	uint32_t mc_seq_rxframing_byte3_d0;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_rxframing_byte3_d1 {
	uint32_t mc_seq_rxframing_byte3_d1;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_rxframing_dbi_d0 {
	uint32_t mc_seq_rxframing_dbi_d0;
	struct { uint32_t
		dbi0   :3-0 +1,
		dbi1   :7-4 +1,
		dbi2   :11-8 +1,
		dbi3   :15-12 +1,
		rsvd0  :31-16 +1;
	};
};

union mc_seq_rxframing_dbi_d1 {
	uint32_t mc_seq_rxframing_dbi_d1;
	struct { uint32_t
		dbi0   :3-0 +1,
		dbi1   :7-4 +1,
		dbi2   :11-8 +1,
		dbi3   :15-12 +1,
		rsvd0  :31-16 +1;
	};
};

union mc_seq_rxframing_edc_d0 {
	uint32_t mc_seq_rxframing_edc_d0;
	struct { uint32_t
		edc0   :3-0 +1,
		edc1   :7-4 +1,
		edc2   :11-8 +1,
		edc3   :15-12 +1,
		wcdr0  :19-16 +1,
		wcdr1  :23-20 +1,
		wcdr2  :27-24 +1,
		wcdr3  :31-28 +1;
	};
};

union mc_seq_rxframing_edc_d1 {
	uint32_t mc_seq_rxframing_edc_d1;
	struct { uint32_t
		edc0   :3-0 +1,
		edc1   :7-4 +1,
		edc2   :11-8 +1,
		edc3   :15-12 +1,
		wcdr0  :19-16 +1,
		wcdr1  :23-20 +1,
		wcdr2  :27-24 +1,
		wcdr3  :31-28 +1;
	};
};

union mc_seq_status_m {
	uint32_t mc_seq_status_m;
	struct { uint32_t
		pwrup_compl_d0          :0-0 +1,
		pwrup_compl_d1          :1-1 +1,
		cmd_rdy_d0              :2-2 +1,
		cmd_rdy_d1              :3-3 +1,
		slf_d0                  :4-4 +1,
		slf_d1                  :5-5 +1,
		ss_slf_d0               :6-6 +1,
		ss_slf_d1               :7-7 +1,
		seq0_arb_cmd_fifo_empty :8-8 +1,
		seq1_arb_cmd_fifo_empty :9-9 +1,
		rsvd0                   :11-10 +1,
		seq0_rs_data_fifo_full  :12-12 +1,
		seq1_rs_data_fifo_full  :13-13 +1,
		seq0_busy               :14-14 +1,
		seq1_busy               :15-15 +1,
		pmg_pwrstate            :16-16 +1,
		rsvd1                   :19-17 +1,
		pmg_fsmstate            :24-20 +1,
		seq0_busy_hys           :25-25 +1,
		seq1_busy_hys           :26-26 +1,
		rsvd2                   :31-27 +1;
	};
};

union mc_seq_status_s {
	uint32_t mc_seq_status_s;
	struct { uint32_t
		seq0_arb_data_fifo_full :0-0 +1,
		seq1_arb_data_fifo_full :1-1 +1,
		rsvd0                   :3-2 +1,
		seq0_arb_cmd_fifo_full  :4-4 +1,
		seq1_arb_cmd_fifo_full  :5-5 +1,
		rsvd1                   :7-6 +1,
		seq0_rs_data_fifo_empty :8-8 +1,
		seq1_rs_data_fifo_empty :9-9 +1,
		rsvd2                   :31-10 +1;
	};
};

union mc_seq_sup_cntl {
	uint32_t mc_seq_sup_cntl;
	struct { uint32_t
		run         :0-0 +1,
		single_step :1-1 +1,
		sw_wake     :2-2 +1,
		reset_pc    :3-3 +1,
		pgm_write   :4-4 +1,
		pgm_read    :5-5 +1,
		fast_write  :6-6 +1,
		bkpt_clear  :7-7 +1,
		rsvd0       :22-8 +1,
		pgm_chksum  :31-23 +1;
	};
};

union mc_seq_sup_dec_stat {
	uint32_t mc_seq_sup_dec_stat;
	struct { uint32_t
		status :31-0 +1;
	};
};

union mc_seq_sup_gp0_stat {
	uint32_t mc_seq_sup_gp0_stat;
	struct { uint32_t
		status :31-0 +1;
	};
};

union mc_seq_sup_gp1_stat {
	uint32_t mc_seq_sup_gp1_stat;
	struct { uint32_t
		status :31-0 +1;
	};
};

union mc_seq_sup_gp2_stat {
	uint32_t mc_seq_sup_gp2_stat;
	struct { uint32_t
		status :31-0 +1;
	};
};

union mc_seq_sup_gp3_stat {
	uint32_t mc_seq_sup_gp3_stat;
	struct { uint32_t
		status :31-0 +1;
	};
};

union mc_seq_sup_ir_stat {
	uint32_t mc_seq_sup_ir_stat;
	struct { uint32_t
		status :31-0 +1;
	};
};

union mc_seq_sup_pgm {
	uint32_t mc_seq_sup_pgm;
	struct { uint32_t
		cntl   :31-0 +1;
	};
};

union mc_seq_sup_pgm_stat {
	uint32_t mc_seq_sup_pgm_stat;
	struct { uint32_t
		status :31-0 +1;
	};
};

union mc_seq_sup_r_pgm {
	uint32_t mc_seq_sup_r_pgm;
	struct { uint32_t
		pgm    :31-0 +1;
	};
};

union mc_seq_tcg_cntl {
	uint32_t mc_seq_tcg_cntl;
	struct { uint32_t
		reset        :0-0 +1,
		enable_d0    :1-1 +1,
		enable_d1    :2-2 +1,
		start        :3-3 +1,
		nfifo        :6-4 +1,
		infinite_cmd :7-7 +1,
		mop          :11-8 +1,
		data_cnt     :15-12 +1,
		load_fifo    :16-16 +1,
		short_ldff   :17-17 +1,
		frame_train  :18-18 +1,
		burst_num    :21-19 +1,
		issue_aref   :22-22 +1,
		txdbi_cntl   :23-23 +1,
		vptr_mask    :24-24 +1,
		aref_last    :25-25 +1,
		aref_both    :26-26 +1,
		rsvd0        :30-27 +1,
		done         :31-31 +1;
	};
};

union mc_seq_timer_rd {
	uint32_t mc_seq_timer_rd;
	struct { uint32_t
		counter :31-0 +1;
	};
};

union mc_seq_timer_wr {
	uint32_t mc_seq_timer_wr;
	struct { uint32_t
		counter :31-0 +1;
	};
};

union mc_seq_train_capture {
	uint32_t mc_seq_train_capture;
	struct { uint32_t
		d0_arf_wakeup             :0-0 +1,
		d1_arf_wakeup             :1-1 +1,
		d0_redc_wakeup            :2-2 +1,
		d1_redc_wakeup            :3-3 +1,
		d0_wedc_wakeup            :4-4 +1,
		d1_wedc_wakeup            :5-5 +1,
		mclk_freq_change_wakeup   :6-6 +1,
		sclk_srbm_ready_wakeup    :7-7 +1,
		d0_cmd_fifo_ready_wakeup  :8-8 +1,
		d1_cmd_fifo_ready_wakeup  :9-9 +1,
		d0_data_fifo_ready_wakeup :10-10 +1,
		d1_data_fifo_ready_wakeup :11-11 +1,
		software_wakeup_wakeup    :12-12 +1,
		reserve0_wakeup           :13-13 +1,
		tsm_done_wakeup           :14-14 +1,
		timer_done_wakeup         :15-15 +1,
		rsvd0                     :16-16 +1,
		tcg_done_wakeup           :17-17 +1,
		allowstop0_wakeup         :18-18 +1,
		allowstop1_wakeup         :19-19 +1,
		dpm_wakeup                :20-20 +1,
		allowstopb0_wakeup        :21-21 +1,
		allowstopb1_wakeup        :22-22 +1,
		dpm_lpt_wakeup            :23-23 +1,
		d0_idleh_wakeup           :24-24 +1,
		d1_idleh_wakeup           :25-25 +1,
		phy_pg_wakeup             :26-26 +1,
		rsvd1                     :31-27 +1;
	};
};

union mc_seq_train_edc_threshold2 {
	uint32_t mc_seq_train_edc_threshold2;
	struct { uint32_t
		threshold_period :31-0 +1;
	};
};

union mc_seq_train_edc_threshold3 {
	uint32_t mc_seq_train_edc_threshold3;
	struct { uint32_t
		ch0_link_retrain_status      :0-0 +1,
		ch1_link_retrain_status      :1-1 +1,
		clear_retrain_status         :2-2 +1,
		retrain_vbi                  :3-3 +1,
		retrain_monitor              :5-4 +1,
		rsvd0                        :7-6 +1,
		ch0_link_retrain_in_progress :8-8 +1,
		ch1_link_retrain_in_progress :9-9 +1,
		rsvd1                        :31-10 +1;
	};
};

union mc_seq_train_edc_threshold {
	uint32_t mc_seq_train_edc_threshold;
	struct { uint32_t
		write_edc_threshold :15-0 +1,
		read_edc_threshold  :31-16 +1;
	};
};

union mc_seq_train_timing {
	uint32_t mc_seq_train_timing;
	struct { uint32_t
		twt2rt :4-0 +1,
		tarf2t :9-5 +1,
		tt2row :14-10 +1,
		tld2ld :19-15 +1,
		rsvd0  :31-20 +1;
	};
};

union mc_seq_train_wakeup_clear {
	uint32_t mc_seq_train_wakeup_clear;
	struct { uint32_t
		d0_arf_wakeup             :0-0 +1,
		d1_arf_wakeup             :1-1 +1,
		d0_redc_wakeup            :2-2 +1,
		d1_redc_wakeup            :3-3 +1,
		d0_wedc_wakeup            :4-4 +1,
		d1_wedc_wakeup            :5-5 +1,
		mclk_freq_change_wakeup   :6-6 +1,
		sclk_srbm_ready_wakeup    :7-7 +1,
		d0_cmd_fifo_ready_wakeup  :8-8 +1,
		d1_cmd_fifo_ready_wakeup  :9-9 +1,
		d0_data_fifo_ready_wakeup :10-10 +1,
		d1_data_fifo_ready_wakeup :11-11 +1,
		software_wakeup_wakeup    :12-12 +1,
		reserve0_wakeup           :13-13 +1,
		tsm_done_wakeup           :14-14 +1,
		timer_done_wakeup         :15-15 +1,
		clearall                  :16-16 +1,
		tcg_done_wakeup           :17-17 +1,
		allowstop0_wakeup         :18-18 +1,
		allowstop1_wakeup         :19-19 +1,
		dpm_wakeup                :20-20 +1,
		allowstopb0_wakeup        :21-21 +1,
		allowstopb1_wakeup        :22-22 +1,
		dpm_lpt_wakeup            :23-23 +1,
		d0_idleh_wakeup           :24-24 +1,
		d1_idleh_wakeup           :25-25 +1,
		phy_pg_wakeup             :26-26 +1,
		rsvd0                     :31-27 +1;
	};
};

union mc_seq_train_wakeup_cntl {
	uint32_t mc_seq_train_wakeup_cntl;
	struct { uint32_t
		boot_up_addr_train        :0-0 +1,
		boot_up_wck_train         :1-1 +1,
		boot_up_read_train        :2-2 +1,
		boot_up_write_train       :3-3 +1,
		self_refresh_addr_train   :4-4 +1,
		self_refresh_wck_train    :5-5 +1,
		self_refresh_read_train   :6-6 +1,
		self_refresh_write_train  :7-7 +1,
		auto_refresh_addr_train   :8-8 +1,
		auto_refresh_wck_train    :9-9 +1,
		auto_refresh_read_train   :10-10 +1,
		auto_refresh_write_train  :11-11 +1,
		write_ecc_addr_train      :12-12 +1,
		write_ecc_wck_train       :13-13 +1,
		write_ecc_read_train      :14-14 +1,
		write_ecc_write_train     :15-15 +1,
		read_ecc_addr_train       :16-16 +1,
		read_ecc_wck_train        :17-17 +1,
		read_ecc_read_train       :18-18 +1,
		read_ecc_write_train      :19-19 +1,
		auto_refresh_wakeup_early :20-20 +1,
		stop_wck_d0               :21-21 +1,
		stop_wck_d1               :22-22 +1,
		rsvd0                     :23-23 +1,
		block_arb_rd_d0           :24-24 +1,
		block_arb_wr_d0           :25-25 +1,
		block_arb_rd_d1           :26-26 +1,
		block_arb_wr_d1           :27-27 +1,
		sw_wakeup                 :28-28 +1,
		disp_astop_wakeup         :29-29 +1,
		train_done_d0             :30-30 +1,
		train_done_d1             :31-31 +1;
	};
};

union mc_seq_train_wakeup_edge {
	uint32_t mc_seq_train_wakeup_edge;
	struct { uint32_t
		d0_arf_wakeup             :0-0 +1,
		d1_arf_wakeup             :1-1 +1,
		d0_redc_wakeup            :2-2 +1,
		d1_redc_wakeup            :3-3 +1,
		d0_wedc_wakeup            :4-4 +1,
		d1_wedc_wakeup            :5-5 +1,
		mclk_freq_change_wakeup   :6-6 +1,
		sclk_srbm_ready_wakeup    :7-7 +1,
		d0_cmd_fifo_ready_wakeup  :8-8 +1,
		d1_cmd_fifo_ready_wakeup  :9-9 +1,
		d0_data_fifo_ready_wakeup :10-10 +1,
		d1_data_fifo_ready_wakeup :11-11 +1,
		software_wakeup_wakeup    :12-12 +1,
		reserve0_wakeup           :13-13 +1,
		tsm_done_wakeup           :14-14 +1,
		timer_done_wakeup         :15-15 +1,
		rsvd0                     :16-16 +1,
		tcg_done_wakeup           :17-17 +1,
		allowstop0_wakeup         :18-18 +1,
		allowstop1_wakeup         :19-19 +1,
		dpm_wakeup                :20-20 +1,
		allowstopb0_wakeup        :21-21 +1,
		allowstopb1_wakeup        :22-22 +1,
		dpm_lpt_wakeup            :23-23 +1,
		d0_idleh_wakeup           :24-24 +1,
		d1_idleh_wakeup           :25-25 +1,
		phy_pg_wakeup             :26-26 +1,
		rsvd1                     :31-27 +1;
	};
};

union mc_seq_train_wakeup_mask {
	uint32_t mc_seq_train_wakeup_mask;
	struct { uint32_t
		d0_arf_wakeup             :0-0 +1,
		d1_arf_wakeup             :1-1 +1,
		d0_redc_wakeup            :2-2 +1,
		d1_redc_wakeup            :3-3 +1,
		d0_wedc_wakeup            :4-4 +1,
		d1_wedc_wakeup            :5-5 +1,
		mclk_freq_change_wakeup   :6-6 +1,
		sclk_srbm_ready_wakeup    :7-7 +1,
		d0_cmd_fifo_ready_wakeup  :8-8 +1,
		d1_cmd_fifo_ready_wakeup  :9-9 +1,
		d0_data_fifo_ready_wakeup :10-10 +1,
		d1_data_fifo_ready_wakeup :11-11 +1,
		software_wakeup_wakeup    :12-12 +1,
		reserve0_wakeup           :13-13 +1,
		tsm_done_wakeup           :14-14 +1,
		timer_done_wakeup         :15-15 +1,
		rsvd0                     :16-16 +1,
		tcg_done_wakeup           :17-17 +1,
		allowstop0_wakeup         :18-18 +1,
		allowstop1_wakeup         :19-19 +1,
		dpm_wakeup                :20-20 +1,
		allowstopb0_wakeup        :21-21 +1,
		allowstopb1_wakeup        :22-22 +1,
		dpm_lpt_wakeup            :23-23 +1,
		d0_idleh_wakeup           :24-24 +1,
		d1_idleh_wakeup           :25-25 +1,
		phy_pg_wakeup             :26-26 +1,
		rsvd1                     :31-27 +1;
	};
};

union mc_seq_tsm_bcnt {
	uint32_t mc_seq_tsm_bcnt;
	struct { uint32_t
		true_act   :3-0 +1,
		false_act  :7-4 +1,
		bcnt_tests :15-8 +1,
		comp_value :23-16 +1,
		done_tests :31-24 +1;
	};
};

union mc_seq_tsm_ctrl {
	uint32_t mc_seq_tsm_ctrl;
	struct { uint32_t
		start         :0-0 +1,
		capture_start :1-1 +1,
		done          :2-2 +1,
		err           :3-3 +1,
		step          :4-4 +1,
		direction     :5-5 +1,
		invert        :6-6 +1,
		mask_bits     :7-7 +1,
		update_loop   :9-8 +1,
		rot_inv       :10-10 +1,
		rsvd0         :15-11 +1,
		pointer       :31-16 +1;
	};
};

union mc_seq_tsm_dbi {
	uint32_t mc_seq_tsm_dbi;
	struct { uint32_t
		dbi    :31-0 +1;
	};
};

union mc_seq_tsm_debug_data {
	uint32_t mc_seq_tsm_debug_data;
	struct { uint32_t
		tsm_debug_data :31-0 +1;
	};
};

union mc_seq_tsm_debug_index {
	uint32_t mc_seq_tsm_debug_index;
	struct { uint32_t
		tsm_debug_index :4-0 +1,
		rsvd0           :31-5 +1;
	};
};

union mc_seq_tsm_edc {
	uint32_t mc_seq_tsm_edc;
	struct { uint32_t
		edc    :31-0 +1;
	};
};

union mc_seq_tsm_flag {
	uint32_t mc_seq_tsm_flag;
	struct { uint32_t
		true_act    :3-0 +1,
		false_act   :7-4 +1,
		flag_tests  :15-8 +1,
		nbbl_mask   :19-16 +1,
		rsvd0       :23-20 +1,
		error_tests :31-24 +1;
	};
};

union mc_seq_tsm_gcnt {
	uint32_t mc_seq_tsm_gcnt;
	struct { uint32_t
		true_act   :3-0 +1,
		false_act  :7-4 +1,
		tests      :15-8 +1,
		comp_value :31-16 +1;
	};
};

union mc_seq_tsm_misc {
	uint32_t mc_seq_tsm_misc;
	struct { uint32_t
		wcdr_ptr  :15-0 +1,
		wcdr_mask :19-16 +1,
		rsvd0     :31-20 +1;
	};
};

union mc_seq_tsm_ncnt {
	uint32_t mc_seq_tsm_ncnt;
	struct { uint32_t
		true_act    :3-0 +1,
		false_act   :7-4 +1,
		tests       :15-8 +1,
		range_low   :19-16 +1,
		range_high  :23-20 +1,
		nibble_skip :27-24 +1,
		rsvd0       :31-28 +1;
	};
};

union mc_seq_tsm_ocnt {
	uint32_t mc_seq_tsm_ocnt;
	struct { uint32_t
		true_act  :3-0 +1,
		false_act :7-4 +1,
		tests     :15-8 +1,
		cmp_value :31-16 +1;
	};
};

union mc_seq_tsm_update {
	uint32_t mc_seq_tsm_update;
	struct { uint32_t
		true_act    :3-0 +1,
		false_act   :7-4 +1,
		updt_tests  :15-8 +1,
		aref_count  :23-16 +1,
		captr_tests :31-24 +1;
	};
};

union mc_seq_tsm_wcdr {
	uint32_t mc_seq_tsm_wcdr;
	struct { uint32_t
		wcdr   :31-0 +1;
	};
};

union mc_seq_txframing_byte0_d0 {
	uint32_t mc_seq_txframing_byte0_d0;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_txframing_byte0_d1 {
	uint32_t mc_seq_txframing_byte0_d1;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_txframing_byte1_d0 {
	uint32_t mc_seq_txframing_byte1_d0;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_txframing_byte1_d1 {
	uint32_t mc_seq_txframing_byte1_d1;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_txframing_byte2_d0 {
	uint32_t mc_seq_txframing_byte2_d0;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_txframing_byte2_d1 {
	uint32_t mc_seq_txframing_byte2_d1;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_txframing_byte3_d0 {
	uint32_t mc_seq_txframing_byte3_d0;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_txframing_byte3_d1 {
	uint32_t mc_seq_txframing_byte3_d1;
	struct { uint32_t
		dq0    :3-0 +1,
		dq1    :7-4 +1,
		dq2    :11-8 +1,
		dq3    :15-12 +1,
		dq4    :19-16 +1,
		dq5    :23-20 +1,
		dq6    :27-24 +1,
		dq7    :31-28 +1;
	};
};

union mc_seq_txframing_dbi_d0 {
	uint32_t mc_seq_txframing_dbi_d0;
	struct { uint32_t
		dbi0   :3-0 +1,
		dbi1   :7-4 +1,
		dbi2   :11-8 +1,
		dbi3   :15-12 +1,
		rsvd0  :31-16 +1;
	};
};

union mc_seq_txframing_dbi_d1 {
	uint32_t mc_seq_txframing_dbi_d1;
	struct { uint32_t
		dbi0   :3-0 +1,
		dbi1   :7-4 +1,
		dbi2   :11-8 +1,
		dbi3   :15-12 +1,
		rsvd0  :31-16 +1;
	};
};

union mc_seq_txframing_edc_d0 {
	uint32_t mc_seq_txframing_edc_d0;
	struct { uint32_t
		edc0   :3-0 +1,
		edc1   :7-4 +1,
		edc2   :11-8 +1,
		edc3   :15-12 +1,
		wcdr0  :19-16 +1,
		wcdr1  :23-20 +1,
		wcdr2  :27-24 +1,
		wcdr3  :31-28 +1;
	};
};

union mc_seq_txframing_edc_d1 {
	uint32_t mc_seq_txframing_edc_d1;
	struct { uint32_t
		edc0   :3-0 +1,
		edc1   :7-4 +1,
		edc2   :11-8 +1,
		edc3   :15-12 +1,
		wcdr0  :19-16 +1,
		wcdr1  :23-20 +1,
		wcdr2  :27-24 +1,
		wcdr3  :31-28 +1;
	};
};

union mc_seq_txframing_fck_d0 {
	uint32_t mc_seq_txframing_fck_d0;
	struct { uint32_t
		fck0   :3-0 +1,
		fck1   :7-4 +1,
		fck2   :11-8 +1,
		fck3   :15-12 +1,
		rsvd0  :31-16 +1;
	};
};

union mc_seq_txframing_fck_d1 {
	uint32_t mc_seq_txframing_fck_d1;
	struct { uint32_t
		fck0   :3-0 +1,
		fck1   :7-4 +1,
		fck2   :11-8 +1,
		fck3   :15-12 +1,
		rsvd0  :31-16 +1;
	};
};

union mc_seq_vendor_id_i0 {
	uint32_t mc_seq_vendor_id_i0;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_vendor_id_i1 {
	uint32_t mc_seq_vendor_id_i1;
	struct { uint32_t
		value  :31-0 +1;
	};
};

union mc_seq_wcdr_ctrl {
	uint32_t mc_seq_wcdr_ctrl;
	struct { uint32_t
		wcdr_pre :7-0 +1,
		wcdr_tim :11-8 +1,
		wr_en    :12-12 +1,
		rd_en    :13-13 +1,
		aref_en  :14-14 +1,
		train_en :15-15 +1,
		twcdrl   :19-16 +1,
		prbs_en  :20-20 +1,
		prbs_rst :21-21 +1,
		rsvd0    :23-22 +1,
		preamble :27-24 +1,
		pre_mask :31-28 +1;
	};
};

union mc_seq_wr_ctl_2 {
	uint32_t mc_seq_wr_ctl_2;
	struct { uint32_t
		dat_dly_h_d0 :0-0 +1,
		dqs_dly_h_d0 :1-1 +1,
		rsvd0        :2-2 +1,
		dat_dly_h_d1 :3-3 +1,
		dqs_dly_h_d1 :4-4 +1,
		rsvd1        :31-5 +1;
	};
};

union mc_seq_wr_ctl_2_lp {
	uint32_t mc_seq_wr_ctl_2_lp;
	struct { uint32_t
		dat_dly_h_d0 :0-0 +1,
		dqs_dly_h_d0 :1-1 +1,
		oen_dly_h_d0 :2-2 +1,
		dat_dly_h_d1 :3-3 +1,
		dqs_dly_h_d1 :4-4 +1,
		oen_dly_h_d1 :5-5 +1,
		wcdr_en      :6-6 +1,
		rsvd0        :31-7 +1;
	};
};

union mc_seq_wr_ctl_2 {
	uint32_t mc_seq_wr_ctl_2;
	struct { uint32_t
		oen_dly_h_d0 :2-2 +1,
		rsvd0        :4-3 +1,
		oen_dly_h_d1 :5-5 +1,
		wcdr_en      :6-6 +1,
		rsvd1        :31-7 +1;
	};
};

union mc_seq_wr_ctl_d0 {
	uint32_t mc_seq_wr_ctl_d0;
	struct { uint32_t
		dat_dly    :3-0 +1,
		dqs_dly    :7-4 +1,
		dqs_xtr    :8-8 +1,
		dat_2y_dly :9-9 +1,
		adr_2y_dly :10-10 +1,
		cmd_2y_dly :11-11 +1,
		rsvd0      :28-12 +1,
		adr_dly    :29-29 +1,
		cmd_dly    :30-30 +1,
		rsvd1      :31-31 +1;
	};
};

union mc_seq_wr_ctl_d0_lp {
	uint32_t mc_seq_wr_ctl_d0_lp;
	struct { uint32_t
		dat_dly    :3-0 +1,
		dqs_dly    :7-4 +1,
		dqs_xtr    :8-8 +1,
		dat_2y_dly :9-9 +1,
		adr_2y_dly :10-10 +1,
		cmd_2y_dly :11-11 +1,
		oen_dly    :15-12 +1,
		oen_ext    :19-16 +1,
		oen_sel    :21-20 +1,
		rsvd0      :23-22 +1,
		odt_dly    :27-24 +1,
		odt_ext    :28-28 +1,
		adr_dly    :29-29 +1,
		cmd_dly    :30-30 +1,
		rsvd1      :31-31 +1;
	};
};

union mc_seq_wr_ctl_d0 {
	uint32_t mc_seq_wr_ctl_d0;
	struct { uint32_t
		oen_dly :15-12 +1,
		oen_ext :19-16 +1,
		oen_sel :21-20 +1,
		rsvd0   :23-22 +1,
		odt_dly :27-24 +1,
		odt_ext :28-28 +1,
		rsvd1   :31-29 +1;
	};
};

union mc_seq_wr_ctl_d1 {
	uint32_t mc_seq_wr_ctl_d1;
	struct { uint32_t
		dat_dly    :3-0 +1,
		dqs_dly    :7-4 +1,
		dqs_xtr    :8-8 +1,
		dat_2y_dly :9-9 +1,
		adr_2y_dly :10-10 +1,
		cmd_2y_dly :11-11 +1,
		rsvd0      :28-12 +1,
		adr_dly    :29-29 +1,
		cmd_dly    :30-30 +1,
		rsvd1      :31-31 +1;
	};
};

union mc_seq_wr_ctl_d1_lp {
	uint32_t mc_seq_wr_ctl_d1_lp;
	struct { uint32_t
		dat_dly    :3-0 +1,
		dqs_dly    :7-4 +1,
		dqs_xtr    :8-8 +1,
		dat_2y_dly :9-9 +1,
		adr_2y_dly :10-10 +1,
		cmd_2y_dly :11-11 +1,
		oen_dly    :15-12 +1,
		oen_ext    :19-16 +1,
		oen_sel    :21-20 +1,
		rsvd0      :23-22 +1,
		odt_dly    :27-24 +1,
		odt_ext    :28-28 +1,
		adr_dly    :29-29 +1,
		cmd_dly    :30-30 +1,
		rsvd1      :31-31 +1;
	};
};

union mc_seq_wr_ctl_d1 {
	uint32_t mc_seq_wr_ctl_d1;
	struct { uint32_t
		oen_dly :15-12 +1,
		oen_ext :19-16 +1,
		oen_sel :21-20 +1,
		rsvd0   :23-22 +1,
		odt_dly :27-24 +1,
		odt_ext :28-28 +1,
		rsvd1   :31-29 +1;
	};
};

union mc_shared_blackout_cntl {
	uint32_t mc_shared_blackout_cntl;
	struct { uint32_t
		blackout_mode :2-0 +1,
		rsvd0         :31-3 +1;
	};
};

union mc_shared_chmap {
	uint32_t mc_shared_chmap;
	struct { uint32_t
		chan0    :3-0 +1,
		chan1    :7-4 +1,
		chan2    :11-8 +1,
		noofchan :15-12 +1,
		rsvd0    :31-16 +1;
	};
};

union mc_shared_chremap {
	uint32_t mc_shared_chremap;
	struct { uint32_t
		chan0  :2-0 +1,
		chan1  :5-3 +1,
		chan2  :8-6 +1,
		chan3  :11-9 +1,
		chan4  :14-12 +1,
		chan5  :17-15 +1,
		chan6  :20-18 +1,
		chan7  :23-21 +1,
		rsvd0  :31-24 +1;
	};
};

union mc_train_edccdr_r_d0 {
	uint32_t mc_train_edccdr_r_d0;
	struct { uint32_t
		edc0   :7-0 +1,
		edc1   :15-8 +1,
		edc2   :23-16 +1,
		edc3   :31-24 +1;
	};
};

union mc_train_edccdr_r_d1 {
	uint32_t mc_train_edccdr_r_d1;
	struct { uint32_t
		edc0   :7-0 +1,
		edc1   :15-8 +1,
		edc2   :23-16 +1,
		edc3   :31-24 +1;
	};
};

union mc_train_edc_status_d0 {
	uint32_t mc_train_edc_status_d0;
	struct { uint32_t
		wedc_cnt :15-0 +1,
		redc_cnt :31-16 +1;
	};
};

union mc_train_edc_status_d1 {
	uint32_t mc_train_edc_status_d1;
	struct { uint32_t
		wedc_cnt :15-0 +1,
		redc_cnt :31-16 +1;
	};
};

union mc_train_prbserr_0_d0 {
	uint32_t mc_train_prbserr_0_d0;
	struct { uint32_t
		dq_status :31-0 +1;
	};
};

union mc_train_prbserr_0_d1 {
	uint32_t mc_train_prbserr_0_d1;
	struct { uint32_t
		dq_status :31-0 +1;
	};
};

union mc_train_prbserr_1_d0 {
	uint32_t mc_train_prbserr_1_d0;
	struct { uint32_t
		dbi_status   :3-0 +1,
		edc_status   :7-4 +1,
		wck_status   :11-8 +1,
		wcdr_status  :15-12 +1,
		rsvd0        :27-16 +1,
		pma_prbsclr  :28-28 +1,
		pmd0_prbsclr :29-29 +1,
		pmd1_prbsclr :30-30 +1,
		rsvd1        :31-31 +1;
	};
};

union mc_train_prbserr_1_d1 {
	uint32_t mc_train_prbserr_1_d1;
	struct { uint32_t
		dbi_status   :3-0 +1,
		edc_status   :7-4 +1,
		wck_status   :11-8 +1,
		wcdr_status  :15-12 +1,
		rsvd0        :27-16 +1,
		pma_prbsclr  :28-28 +1,
		pmd0_prbsclr :29-29 +1,
		pmd1_prbsclr :30-30 +1,
		rsvd1        :31-31 +1;
	};
};

union mc_train_prbserr_2_d0 {
	uint32_t mc_train_prbserr_2_d0;
	struct { uint32_t
		ck_status   :0-0 +1,
		ckb_status  :1-1 +1,
		rsvd0       :3-2 +1,
		cs_status   :5-4 +1,
		rsvd1       :7-6 +1,
		cke_status  :8-8 +1,
		ras_status  :9-9 +1,
		cas_status  :10-10 +1,
		we_status   :11-11 +1,
		rsvd2       :15-12 +1,
		addr_status :25-16 +1,
		rsvd3       :27-26 +1,
		abi_status  :28-28 +1,
		rsvd4       :31-29 +1;
	};
};

union mc_train_prbserr_2_d1 {
	uint32_t mc_train_prbserr_2_d1;
	struct { uint32_t
		ck_status   :0-0 +1,
		ckb_status  :1-1 +1,
		rsvd0       :3-2 +1,
		cs_status   :5-4 +1,
		rsvd1       :7-6 +1,
		cke_status  :8-8 +1,
		ras_status  :9-9 +1,
		cas_status  :10-10 +1,
		we_status   :11-11 +1,
		rsvd2       :15-12 +1,
		addr_status :25-16 +1,
		rsvd3       :27-26 +1,
		abi_status  :28-28 +1,
		rsvd4       :31-29 +1;
	};
};

union mc_tsm_debug_bcnt0 {
	uint32_t mc_tsm_debug_bcnt0;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt10 {
	uint32_t mc_tsm_debug_bcnt10;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt1 {
	uint32_t mc_tsm_debug_bcnt1;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt2 {
	uint32_t mc_tsm_debug_bcnt2;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt3 {
	uint32_t mc_tsm_debug_bcnt3;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt4 {
	uint32_t mc_tsm_debug_bcnt4;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt5 {
	uint32_t mc_tsm_debug_bcnt5;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt6 {
	uint32_t mc_tsm_debug_bcnt6;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt7 {
	uint32_t mc_tsm_debug_bcnt7;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt8 {
	uint32_t mc_tsm_debug_bcnt8;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bcnt9 {
	uint32_t mc_tsm_debug_bcnt9;
	struct { uint32_t
		byte0  :7-0 +1,
		byte1  :15-8 +1,
		byte2  :23-16 +1,
		byte3  :31-24 +1;
	};
};

union mc_tsm_debug_bkpt {
	uint32_t mc_tsm_debug_bkpt;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_tsm_debug_flag {
	uint32_t mc_tsm_debug_flag;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_tsm_debug_gcnt {
	uint32_t mc_tsm_debug_gcnt;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_tsm_debug_misc {
	uint32_t mc_tsm_debug_misc;
	struct { uint32_t
		flag    :7-0 +1,
		ncnt_rd :11-8 +1,
		ncnt_wr :15-12 +1,
		rsvd0   :31-16 +1;
	};
};

union mc_tsm_debug_st01 {
	uint32_t mc_tsm_debug_st01;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_tsm_debug_st23 {
	uint32_t mc_tsm_debug_st23;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_tsm_debug_st45 {
	uint32_t mc_tsm_debug_st45;
	struct { uint32_t
		data   :31-0 +1;
	};
};

union mc_vm_agp_base {
	uint32_t mc_vm_agp_base;
	struct { uint32_t
		agp_base :17-0 +1,
		rsvd0    :31-18 +1;
	};
};

union mc_vm_agp_bot {
	uint32_t mc_vm_agp_bot;
	struct { uint32_t
		agp_bot :17-0 +1,
		rsvd0   :31-18 +1;
	};
};

union mc_vm_agp_top {
	uint32_t mc_vm_agp_top;
	struct { uint32_t
		agp_top :17-0 +1,
		rsvd0   :31-18 +1;
	};
};

union mc_vm_dc_write_cntl {
	uint32_t mc_vm_dc_write_cntl;
	struct { uint32_t
		dc_write_hit_region_0_mode :1-0 +1,
		dc_write_hit_region_1_mode :3-2 +1,
		dc_write_hit_region_2_mode :5-4 +1,
		dc_write_hit_region_3_mode :7-6 +1,
		dc_memory_write_local      :8-8 +1,
		dc_memory_write_system     :9-9 +1,
		rsvd0                      :31-10 +1;
	};
};

union mc_vm_dc_write_hit_region_0_high_addr {
	uint32_t mc_vm_dc_write_hit_region_0_high_addr;
	struct { uint32_t
		physical_address :27-0 +1,
		rsvd0            :31-28 +1;
	};
};

union mc_vm_dc_write_hit_region_0_low_addr {
	uint32_t mc_vm_dc_write_hit_region_0_low_addr;
	struct { uint32_t
		physical_address :27-0 +1,
		rsvd0            :31-28 +1;
	};
};

union mc_vm_dc_write_hit_region_1_high_addr {
	uint32_t mc_vm_dc_write_hit_region_1_high_addr;
	struct { uint32_t
		physical_address :27-0 +1,
		rsvd0            :31-28 +1;
	};
};

union mc_vm_dc_write_hit_region_1_low_addr {
	uint32_t mc_vm_dc_write_hit_region_1_low_addr;
	struct { uint32_t
		physical_address :27-0 +1,
		rsvd0            :31-28 +1;
	};
};

union mc_vm_dc_write_hit_region_2_high_addr {
	uint32_t mc_vm_dc_write_hit_region_2_high_addr;
	struct { uint32_t
		physical_address :27-0 +1,
		rsvd0            :31-28 +1;
	};
};

union mc_vm_dc_write_hit_region_2_low_addr {
	uint32_t mc_vm_dc_write_hit_region_2_low_addr;
	struct { uint32_t
		physical_address :27-0 +1,
		rsvd0            :31-28 +1;
	};
};

union mc_vm_dc_write_hit_region_3_high_addr {
	uint32_t mc_vm_dc_write_hit_region_3_high_addr;
	struct { uint32_t
		physical_address :27-0 +1,
		rsvd0            :31-28 +1;
	};
};

union mc_vm_dc_write_hit_region_3_low_addr {
	uint32_t mc_vm_dc_write_hit_region_3_low_addr;
	struct { uint32_t
		physical_address :27-0 +1,
		rsvd0            :31-28 +1;
	};
};

union mc_vm_fb_location {
	uint32_t mc_vm_fb_location;
	struct { uint32_t
		fb_base :15-0 +1,
		fb_top  :31-16 +1;
	};
};

union mc_vm_fb_offset {
	uint32_t mc_vm_fb_offset;
	struct { uint32_t
		fb_offset :17-0 +1,
		rsvd0     :31-18 +1;
	};
};

union mc_vm_mb_l1_tlb0_debug {
	uint32_t mc_vm_mb_l1_tlb0_debug;
	struct { uint32_t
		invalidate_l1_tlb       :0-0 +1,
		rsvd0                   :7-1 +1,
		send_free_at_rtn        :8-8 +1,
		effective_l1_tlb_size   :11-9 +1,
		effective_l1_queue_size :14-12 +1,
		l1_tlb_debug            :18-15 +1,
		rsvd1                   :31-19 +1;
	};
};

union mc_vm_mb_l1_tlb0_status {
	uint32_t mc_vm_mb_l1_tlb0_status;
	struct { uint32_t
		busy   :0-0 +1,
		rsvd0  :31-1 +1;
	};
};

union mc_vm_mb_l1_tlb1_status {
	uint32_t mc_vm_mb_l1_tlb1_status;
	struct { uint32_t
		busy   :0-0 +1,
		rsvd0  :31-1 +1;
	};
};

union mc_vm_mb_l1_tlb2_debug {
	uint32_t mc_vm_mb_l1_tlb2_debug;
	struct { uint32_t
		invalidate_l1_tlb       :0-0 +1,
		rsvd0                   :7-1 +1,
		send_free_at_rtn        :8-8 +1,
		effective_l1_tlb_size   :11-9 +1,
		effective_l1_queue_size :14-12 +1,
		l1_tlb_debug            :18-15 +1,
		rsvd1                   :31-19 +1;
	};
};

union mc_vm_mb_l1_tlb2_status {
	uint32_t mc_vm_mb_l1_tlb2_status;
	struct { uint32_t
		busy   :0-0 +1,
		rsvd0  :31-1 +1;
	};
};

union mc_vm_mb_l1_tlb3_debug {
	uint32_t mc_vm_mb_l1_tlb3_debug;
	struct { uint32_t
		invalidate_l1_tlb       :0-0 +1,
		rsvd0                   :7-1 +1,
		send_free_at_rtn        :8-8 +1,
		effective_l1_tlb_size   :11-9 +1,
		effective_l1_queue_size :14-12 +1,
		l1_tlb_debug            :18-15 +1,
		rsvd1                   :31-19 +1;
	};
};

union mc_vm_mb_l1_tlb3_status {
	uint32_t mc_vm_mb_l1_tlb3_status;
	struct { uint32_t
		busy   :0-0 +1,
		rsvd0  :31-1 +1;
	};
};

union mc_vm_mb_l2arbiter_l2_credits {
	uint32_t mc_vm_mb_l2arbiter_l2_credits;
	struct { uint32_t
		l2_if_credits :5-0 +1,
		rsvd0         :31-6 +1;
	};
};

union mc_vm_md_l1_tlb0_debug {
	uint32_t mc_vm_md_l1_tlb0_debug;
	struct { uint32_t
		invalidate_l1_tlb       :0-0 +1,
		rsvd0                   :7-1 +1,
		send_free_at_rtn        :8-8 +1,
		effective_l1_tlb_size   :11-9 +1,
		effective_l1_queue_size :14-12 +1,
		l1_tlb_debug            :18-15 +1,
		rsvd1                   :31-19 +1;
	};
};

union mc_vm_md_l1_tlb0_status {
	uint32_t mc_vm_md_l1_tlb0_status;
	struct { uint32_t
		busy   :0-0 +1,
		rsvd0  :31-1 +1;
	};
};

union mc_vm_md_l1_tlb1_debug {
	uint32_t mc_vm_md_l1_tlb1_debug;
	struct { uint32_t
		invalidate_l1_tlb       :0-0 +1,
		rsvd0                   :7-1 +1,
		send_free_at_rtn        :8-8 +1,
		effective_l1_tlb_size   :11-9 +1,
		effective_l1_queue_size :14-12 +1,
		l1_tlb_debug            :18-15 +1,
		rsvd1                   :31-19 +1;
	};
};

union mc_vm_md_l1_tlb1_status {
	uint32_t mc_vm_md_l1_tlb1_status;
	struct { uint32_t
		busy   :0-0 +1,
		rsvd0  :31-1 +1;
	};
};

union mc_vm_md_l1_tlb2_debug {
	uint32_t mc_vm_md_l1_tlb2_debug;
	struct { uint32_t
		invalidate_l1_tlb       :0-0 +1,
		rsvd0                   :7-1 +1,
		send_free_at_rtn        :8-8 +1,
		effective_l1_tlb_size   :11-9 +1,
		effective_l1_queue_size :14-12 +1,
		l1_tlb_debug            :18-15 +1,
		rsvd1                   :31-19 +1;
	};
};

union mc_vm_md_l1_tlb2_status {
	uint32_t mc_vm_md_l1_tlb2_status;
	struct { uint32_t
		busy   :0-0 +1,
		rsvd0  :31-1 +1;
	};
};

union mc_vm_md_l1_tlb3_debug {
	uint32_t mc_vm_md_l1_tlb3_debug;
	struct { uint32_t
		invalidate_l1_tlb       :0-0 +1,
		rsvd0                   :7-1 +1,
		send_free_at_rtn        :8-8 +1,
		effective_l1_tlb_size   :11-9 +1,
		effective_l1_queue_size :14-12 +1,
		l1_tlb_debug            :18-15 +1,
		rsvd1                   :31-19 +1;
	};
};

union mc_vm_md_l1_tlb3_status {
	uint32_t mc_vm_md_l1_tlb3_status;
	struct { uint32_t
		busy   :0-0 +1,
		rsvd0  :31-1 +1;
	};
};

union mc_vm_md_l2arbiter_l2_credits {
	uint32_t mc_vm_md_l2arbiter_l2_credits;
	struct { uint32_t
		l2_if_credits :5-0 +1,
		rsvd0         :31-6 +1;
	};
};

union mc_vm_mx_l1_tlb_cntl {
	uint32_t mc_vm_mx_l1_tlb_cntl;
	struct { uint32_t
		enable_l1_tlb                   :0-0 +1,
		enable_l1_fragment_processing   :1-1 +1,
		rsvd0                           :2-2 +1,
		system_access_mode              :4-3 +1,
		system_aperture_unmapped_access :5-5 +1,
		enable_advanced_driver_model    :6-6 +1,
		eco_bits                        :10-7 +1,
		rsvd1                           :31-11 +1;
	};
};

union mc_vm_system_aperture_default_addr {
	uint32_t mc_vm_system_aperture_default_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union mc_vm_system_aperture_high_addr {
	uint32_t mc_vm_system_aperture_high_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union mc_vm_system_aperture_low_addr {
	uint32_t mc_vm_system_aperture_low_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union mc_wr_cb {
	uint32_t mc_wr_cb;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_wr_db {
	uint32_t mc_wr_db;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_wr_grp_ext {
	uint32_t mc_wr_grp_ext;
	struct { uint32_t
		dbsten0 :3-0 +1,
		tc0     :7-4 +1,
		rsvd0   :31-8 +1;
	};
};

union mc_wr_grp_gfx {
	uint32_t mc_wr_grp_gfx;
	struct { uint32_t
		cp     :3-0 +1,
		rsvd0  :11-4 +1,
		xdma   :15-12 +1,
		xdmam  :19-16 +1,
		rsvd1  :31-20 +1;
	};
};

union mc_wr_grp_lcl {
	uint32_t mc_wr_grp_lcl;
	struct { uint32_t
		cb0      :3-0 +1,
		cbcmask0 :7-4 +1,
		cbfmask0 :11-8 +1,
		db0      :15-12 +1,
		dbhtile0 :19-16 +1,
		sx0      :23-20 +1,
		rsvd0    :27-24 +1,
		cbimmed0 :31-28 +1;
	};
};

union mc_wr_grp_oth {
	uint32_t mc_wr_grp_oth;
	struct { uint32_t
		uvd_ext0 :3-0 +1,
		rsvd0    :7-4 +1,
		hdp      :11-8 +1,
		sem      :15-12 +1,
		umc      :19-16 +1,
		uvd      :23-20 +1,
		xdp      :27-24 +1,
		uvd_ext1 :31-28 +1;
	};
};

union mc_wr_grp_sys {
	uint32_t mc_wr_grp_sys;
	struct { uint32_t
		ih     :3-0 +1,
		mcif   :7-4 +1,
		rlc    :11-8 +1,
		rsvd0  :19-12 +1,
		smu    :23-20 +1,
		vce    :27-24 +1,
		vceu   :31-28 +1;
	};
};

union mc_wr_hub {
	uint32_t mc_wr_hub;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_wr_tc0 {
	uint32_t mc_wr_tc0;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_wr_tc1 {
	uint32_t mc_wr_tc1;
	struct { uint32_t
		enable             :0-0 +1,
		prescale           :2-1 +1,
		blackout_exempt    :3-3 +1,
		stall_mode         :5-4 +1,
		stall_override     :6-6 +1,
		max_burst          :10-7 +1,
		lazy_timer         :14-11 +1,
		stall_override_wtm :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union mc_xbar_addr_dec {
	uint32_t mc_xbar_addr_dec;
	struct { uint32_t
		no_div_by_3    :0-0 +1,
		gecc           :1-1 +1,
		rb_split       :2-2 +1,
		rb_split_colhi :3-3 +1,
		rsvd0          :31-4 +1;
	};
};

union mc_xbar_arb {
	uint32_t mc_xbar_arb;
	struct { uint32_t
		hubrd_highest             :0-0 +1,
		disable_hub_stall_highest :1-1 +1,
		break_burst_cid_change    :2-2 +1,
		rsvd0                     :31-3 +1;
	};
};

union mc_xbar_arb_max_burst {
	uint32_t mc_xbar_arb_max_burst;
	struct { uint32_t
		rd_port0 :3-0 +1,
		rd_port1 :7-4 +1,
		rd_port2 :11-8 +1,
		rd_port3 :15-12 +1,
		wr_port0 :19-16 +1,
		wr_port1 :23-20 +1,
		wr_port2 :27-24 +1,
		wr_port3 :31-28 +1;
	};
};

union mc_xbar_chtriremap {
	uint32_t mc_xbar_chtriremap;
	struct { uint32_t
		ch0    :1-0 +1,
		ch1    :3-2 +1,
		ch2    :5-4 +1,
		rsvd0  :31-6 +1;
	};
};

union mc_xbar_perf_mon_cntl0 {
	uint32_t mc_xbar_perf_mon_cntl0;
	struct { uint32_t
		start_thresh :11-0 +1,
		stop_thresh  :23-12 +1,
		start_mode   :25-24 +1,
		stop_mode    :27-26 +1,
		allow_wrap   :28-28 +1,
		rsvd0        :31-29 +1;
	};
};

union mc_xbar_perf_mon_cntl1 {
	uint32_t mc_xbar_perf_mon_cntl1;
	struct { uint32_t
		thresh_cntr_id :7-0 +1,
		start_trig_id  :15-8 +1,
		stop_trig_id   :23-16 +1,
		rsvd0          :31-24 +1;
	};
};

union mc_xbar_perf_mon_cntl2 {
	uint32_t mc_xbar_perf_mon_cntl2;
	struct { uint32_t
		mon0_id :7-0 +1,
		mon1_id :15-8 +1,
		mon2_id :23-16 +1,
		mon3_id :31-24 +1;
	};
};

union mc_xbar_perf_mon_max_thsh {
	uint32_t mc_xbar_perf_mon_max_thsh;
	struct { uint32_t
		mon0   :7-0 +1,
		mon1   :15-8 +1,
		mon2   :23-16 +1,
		mon3   :31-24 +1;
	};
};

union mc_xbar_perf_mon_rslt0 {
	uint32_t mc_xbar_perf_mon_rslt0;
	struct { uint32_t
		count  :31-0 +1;
	};
};

union mc_xbar_perf_mon_rslt1 {
	uint32_t mc_xbar_perf_mon_rslt1;
	struct { uint32_t
		count  :31-0 +1;
	};
};

union mc_xbar_perf_mon_rslt2 {
	uint32_t mc_xbar_perf_mon_rslt2;
	struct { uint32_t
		count  :31-0 +1;
	};
};

union mc_xbar_perf_mon_rslt3 {
	uint32_t mc_xbar_perf_mon_rslt3;
	struct { uint32_t
		count  :31-0 +1;
	};
};

union mc_xbar_rdreq_credit {
	uint32_t mc_xbar_rdreq_credit;
	struct { uint32_t
		out0   :7-0 +1,
		out1   :15-8 +1,
		out2   :23-16 +1,
		out3   :31-24 +1;
	};
};

union mc_xbar_rdreq_pri_credit {
	uint32_t mc_xbar_rdreq_pri_credit;
	struct { uint32_t
		out0   :7-0 +1,
		out1   :15-8 +1,
		out2   :23-16 +1,
		out3   :31-24 +1;
	};
};

union mc_xbar_rdret_credit1 {
	uint32_t mc_xbar_rdret_credit1;
	struct { uint32_t
		out0   :7-0 +1,
		out1   :15-8 +1,
		out2   :23-16 +1,
		out3   :31-24 +1;
	};
};

union mc_xbar_rdret_credit2 {
	uint32_t mc_xbar_rdret_credit2;
	struct { uint32_t
		out4              :7-0 +1,
		out5              :15-8 +1,
		hub_lp_rdret_skid :23-16 +1,
		rsvd0             :31-24 +1;
	};
};

union mc_xbar_rdret_pri_credit1 {
	uint32_t mc_xbar_rdret_pri_credit1;
	struct { uint32_t
		out0   :7-0 +1,
		out1   :15-8 +1,
		out2   :23-16 +1,
		out3   :31-24 +1;
	};
};

union mc_xbar_rdret_pri_credit2 {
	uint32_t mc_xbar_rdret_pri_credit2;
	struct { uint32_t
		out4   :7-0 +1,
		out5   :15-8 +1,
		rsvd0  :31-16 +1;
	};
};

union mc_xbar_remote {
	uint32_t mc_xbar_remote;
	struct { uint32_t
		wrreq_en_goq :0-0 +1,
		rdreq_en_goq :1-1 +1,
		rsvd0        :31-2 +1;
	};
};

union mc_xbar_spare0 {
	uint32_t mc_xbar_spare0;
	struct { uint32_t
		bit    :31-0 +1;
	};
};

union mc_xbar_spare1 {
	uint32_t mc_xbar_spare1;
	struct { uint32_t
		bit    :31-0 +1;
	};
};

union mc_xbar_twochan {
	uint32_t mc_xbar_twochan;
	struct { uint32_t
		disable_oneport :0-0 +1,
		ch0             :2-1 +1,
		ch1             :4-3 +1,
		rsvd0           :31-5 +1;
	};
};

union mc_xbar_wrreq_credit {
	uint32_t mc_xbar_wrreq_credit;
	struct { uint32_t
		out0   :7-0 +1,
		out1   :15-8 +1,
		out2   :23-16 +1,
		out3   :31-24 +1;
	};
};

union mc_xbar_wrret_credit1 {
	uint32_t mc_xbar_wrret_credit1;
	struct { uint32_t
		out0   :7-0 +1,
		out1   :15-8 +1,
		out2   :23-16 +1,
		out3   :31-24 +1;
	};
};

union mc_xbar_wrret_credit2 {
	uint32_t mc_xbar_wrret_credit2;
	struct { uint32_t
		out4   :7-0 +1,
		out5   :15-8 +1,
		rsvd0  :31-16 +1;
	};
};

union mc_xpb_clg_cfg0 {
	uint32_t mc_xpb_clg_cfg0;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg10 {
	uint32_t mc_xpb_clg_cfg10;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg11 {
	uint32_t mc_xpb_clg_cfg11;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg12 {
	uint32_t mc_xpb_clg_cfg12;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg13 {
	uint32_t mc_xpb_clg_cfg13;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg14 {
	uint32_t mc_xpb_clg_cfg14;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg15 {
	uint32_t mc_xpb_clg_cfg15;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg16 {
	uint32_t mc_xpb_clg_cfg16;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg17 {
	uint32_t mc_xpb_clg_cfg17;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg18 {
	uint32_t mc_xpb_clg_cfg18;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg19 {
	uint32_t mc_xpb_clg_cfg19;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg1 {
	uint32_t mc_xpb_clg_cfg1;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg20 {
	uint32_t mc_xpb_clg_cfg20;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg21 {
	uint32_t mc_xpb_clg_cfg21;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg22 {
	uint32_t mc_xpb_clg_cfg22;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg23 {
	uint32_t mc_xpb_clg_cfg23;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg24 {
	uint32_t mc_xpb_clg_cfg24;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg25 {
	uint32_t mc_xpb_clg_cfg25;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg26 {
	uint32_t mc_xpb_clg_cfg26;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg27 {
	uint32_t mc_xpb_clg_cfg27;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg28 {
	uint32_t mc_xpb_clg_cfg28;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg29 {
	uint32_t mc_xpb_clg_cfg29;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg2 {
	uint32_t mc_xpb_clg_cfg2;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg30 {
	uint32_t mc_xpb_clg_cfg30;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg31 {
	uint32_t mc_xpb_clg_cfg31;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg32 {
	uint32_t mc_xpb_clg_cfg32;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg33 {
	uint32_t mc_xpb_clg_cfg33;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg34 {
	uint32_t mc_xpb_clg_cfg34;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg35 {
	uint32_t mc_xpb_clg_cfg35;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg36 {
	uint32_t mc_xpb_clg_cfg36;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg3 {
	uint32_t mc_xpb_clg_cfg3;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg4 {
	uint32_t mc_xpb_clg_cfg4;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg5 {
	uint32_t mc_xpb_clg_cfg5;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg6 {
	uint32_t mc_xpb_clg_cfg6;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg7 {
	uint32_t mc_xpb_clg_cfg7;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg8 {
	uint32_t mc_xpb_clg_cfg8;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_cfg9 {
	uint32_t mc_xpb_clg_cfg9;
	struct { uint32_t
		wcb_num    :3-0 +1,
		lb_type    :6-4 +1,
		p2p_bar    :9-7 +1,
		host_flush :13-10 +1,
		side_flush :17-14 +1,
		rsvd0      :31-18 +1;
	};
};

union mc_xpb_clg_extra {
	uint32_t mc_xpb_clg_extra;
	struct { uint32_t
		cmp0   :7-0 +1,
		msk0   :15-8 +1,
		rsvd0  :16-16 +1,
		cmp1   :24-17 +1,
		rsvd1  :31-25 +1;
	};
};

union mc_xpb_clg_extra_rd {
	uint32_t mc_xpb_clg_extra_rd;
	struct { uint32_t
		cmp0   :7-0 +1,
		msk0   :15-8 +1,
		vld0   :16-16 +1,
		cmp1   :24-17 +1,
		vld1   :25-25 +1,
		rsvd0  :31-26 +1;
	};
};

union mc_xpb_clg_extra {
	uint32_t mc_xpb_clg_extra;
	struct { uint32_t
		vld0   :16-16 +1,
		rsvd0  :24-17 +1,
		vld1   :25-25 +1,
		rsvd1  :31-26 +1;
	};
};

union mc_xpb_clk_gat {
	uint32_t mc_xpb_clk_gat;
	struct { uint32_t
		ondly         :5-0 +1,
		offdly        :11-6 +1,
		rdydly        :17-12 +1,
		enable        :18-18 +1,
		mem_ls_enable :19-19 +1,
		rsvd0         :31-20 +1;
	};
};

union mc_xpb_intf_cfg2 {
	uint32_t mc_xpb_intf_cfg2;
	struct { uint32_t
		rpb_rdreq_crd :7-0 +1,
		rsvd0         :31-8 +1;
	};
};

union mc_xpb_intf_cfg {
	uint32_t mc_xpb_intf_cfg;
	struct { uint32_t
		rpb_wrreq_crd     :7-0 +1,
		mc_wrret_ask      :15-8 +1,
		xsp_req_crd       :22-16 +1,
		bif_reg_snoop_sel :23-23 +1,
		bif_reg_snoop_val :24-24 +1,
		bif_mem_snoop_sel :25-25 +1,
		bif_mem_snoop_val :26-26 +1,
		xsp_snoop_sel     :28-27 +1,
		xsp_snoop_val     :29-29 +1,
		xsp_ordering_sel  :30-30 +1,
		xsp_ordering_val  :31-31 +1;
	};
};

union mc_xpb_intf_sts {
	uint32_t mc_xpb_intf_sts;
	struct { uint32_t
		rpb_wrreq_crd     :7-0 +1,
		xsp_req_crd       :14-8 +1,
		hop_data_buf_full :15-15 +1,
		hop_attr_buf_full :16-16 +1,
		cns_buf_full      :17-17 +1,
		cns_buf_busy      :18-18 +1,
		rpb_rdreq_crd     :26-19 +1,
		rsvd0             :31-27 +1;
	};
};

union mc_xpb_lb_addr {
	uint32_t mc_xpb_lb_addr;
	struct { uint32_t
		cmp0   :9-0 +1,
		mask0  :19-10 +1,
		cmp1   :25-20 +1,
		mask1  :31-26 +1;
	};
};

union mc_xpb_map_invert_flush_num_lsb {
	uint32_t mc_xpb_map_invert_flush_num_lsb;
	struct { uint32_t
		alter_flush_num :15-0 +1,
		rsvd0           :31-16 +1;
	};
};

union mc_xpb_misc_cfg {
	uint32_t mc_xpb_misc_cfg;
	struct { uint32_t
		fieldname0  :7-0 +1,
		fieldname1  :15-8 +1,
		fieldname2  :23-16 +1,
		fieldname3  :30-24 +1,
		triggername :31-31 +1;
	};
};

union mc_xpb_p2p_bar0 {
	uint32_t mc_xpb_p2p_bar0;
	struct { uint32_t
		host_flush   :3-0 +1,
		reg_sys_bar  :7-4 +1,
		mem_sys_bar  :11-8 +1,
		valid        :12-12 +1,
		send_dis     :13-13 +1,
		compress_dis :14-14 +1,
		reserved     :15-15 +1,
		address      :31-16 +1;
	};
};

union mc_xpb_p2p_bar1 {
	uint32_t mc_xpb_p2p_bar1;
	struct { uint32_t
		host_flush   :3-0 +1,
		reg_sys_bar  :7-4 +1,
		mem_sys_bar  :11-8 +1,
		valid        :12-12 +1,
		send_dis     :13-13 +1,
		compress_dis :14-14 +1,
		reserved     :15-15 +1,
		address      :31-16 +1;
	};
};

union mc_xpb_p2p_bar2 {
	uint32_t mc_xpb_p2p_bar2;
	struct { uint32_t
		host_flush   :3-0 +1,
		reg_sys_bar  :7-4 +1,
		mem_sys_bar  :11-8 +1,
		valid        :12-12 +1,
		send_dis     :13-13 +1,
		compress_dis :14-14 +1,
		reserved     :15-15 +1,
		address      :31-16 +1;
	};
};

union mc_xpb_p2p_bar3 {
	uint32_t mc_xpb_p2p_bar3;
	struct { uint32_t
		host_flush   :3-0 +1,
		reg_sys_bar  :7-4 +1,
		mem_sys_bar  :11-8 +1,
		valid        :12-12 +1,
		send_dis     :13-13 +1,
		compress_dis :14-14 +1,
		reserved     :15-15 +1,
		address      :31-16 +1;
	};
};

union mc_xpb_p2p_bar4 {
	uint32_t mc_xpb_p2p_bar4;
	struct { uint32_t
		host_flush   :3-0 +1,
		reg_sys_bar  :7-4 +1,
		mem_sys_bar  :11-8 +1,
		valid        :12-12 +1,
		send_dis     :13-13 +1,
		compress_dis :14-14 +1,
		reserved     :15-15 +1,
		address      :31-16 +1;
	};
};

union mc_xpb_p2p_bar5 {
	uint32_t mc_xpb_p2p_bar5;
	struct { uint32_t
		host_flush   :3-0 +1,
		reg_sys_bar  :7-4 +1,
		mem_sys_bar  :11-8 +1,
		valid        :12-12 +1,
		send_dis     :13-13 +1,
		compress_dis :14-14 +1,
		reserved     :15-15 +1,
		address      :31-16 +1;
	};
};

union mc_xpb_p2p_bar6 {
	uint32_t mc_xpb_p2p_bar6;
	struct { uint32_t
		host_flush   :3-0 +1,
		reg_sys_bar  :7-4 +1,
		mem_sys_bar  :11-8 +1,
		valid        :12-12 +1,
		send_dis     :13-13 +1,
		compress_dis :14-14 +1,
		reserved     :15-15 +1,
		address      :31-16 +1;
	};
};

union mc_xpb_p2p_bar7 {
	uint32_t mc_xpb_p2p_bar7;
	struct { uint32_t
		host_flush   :3-0 +1,
		reg_sys_bar  :7-4 +1,
		mem_sys_bar  :11-8 +1,
		valid        :12-12 +1,
		send_dis     :13-13 +1,
		compress_dis :14-14 +1,
		reserved     :15-15 +1,
		address      :31-16 +1;
	};
};

union mc_xpb_p2p_bar_cfg {
	uint32_t mc_xpb_p2p_bar_cfg;
	struct { uint32_t
		addr_size          :3-0 +1,
		send_bar           :5-4 +1,
		snoop              :6-6 +1,
		send_dis           :7-7 +1,
		compress_dis       :8-8 +1,
		update_dis         :9-9 +1,
		regbar_from_sysbar :10-10 +1,
		rd_en              :11-11 +1,
		atc_translated     :12-12 +1,
		rsvd0              :31-13 +1;
	};
};

union mc_xpb_p2p_bar_debug {
	uint32_t mc_xpb_p2p_bar_debug;
	struct { uint32_t
		sel         :7-0 +1,
		host_flush  :11-8 +1,
		mem_sys_bar :15-12 +1,
		rsvd0       :31-16 +1;
	};
};

union mc_xpb_p2p_bar_delta_above {
	uint32_t mc_xpb_p2p_bar_delta_above;
	struct { uint32_t
		en     :7-0 +1,
		delta  :27-8 +1,
		rsvd0  :31-28 +1;
	};
};

union mc_xpb_p2p_bar_delta_below {
	uint32_t mc_xpb_p2p_bar_delta_below;
	struct { uint32_t
		en     :7-0 +1,
		delta  :27-8 +1,
		rsvd0  :31-28 +1;
	};
};

union mc_xpb_p2p_bar_setup {
	uint32_t mc_xpb_p2p_bar_setup;
	struct { uint32_t
		sel          :7-0 +1,
		reg_sys_bar  :11-8 +1,
		valid        :12-12 +1,
		send_dis     :13-13 +1,
		compress_dis :14-14 +1,
		reserved     :15-15 +1,
		address      :31-16 +1;
	};
};

union mc_xpb_peer_sys_bar0 {
	uint32_t mc_xpb_peer_sys_bar0;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_peer_sys_bar1 {
	uint32_t mc_xpb_peer_sys_bar1;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_peer_sys_bar2 {
	uint32_t mc_xpb_peer_sys_bar2;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_peer_sys_bar3 {
	uint32_t mc_xpb_peer_sys_bar3;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_peer_sys_bar4 {
	uint32_t mc_xpb_peer_sys_bar4;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_peer_sys_bar5 {
	uint32_t mc_xpb_peer_sys_bar5;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_peer_sys_bar6 {
	uint32_t mc_xpb_peer_sys_bar6;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_peer_sys_bar7 {
	uint32_t mc_xpb_peer_sys_bar7;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_peer_sys_bar8 {
	uint32_t mc_xpb_peer_sys_bar8;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_peer_sys_bar9 {
	uint32_t mc_xpb_peer_sys_bar9;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_perf_knobs {
	uint32_t mc_xpb_perf_knobs;
	struct { uint32_t
		cns_fifo_depth     :5-0 +1,
		wcb_hst_fifo_depth :11-6 +1,
		wcb_sid_fifo_depth :17-12 +1,
		rsvd0              :31-18 +1;
	};
};

union mc_xpb_pipe_sts {
	uint32_t mc_xpb_pipe_sts;
	struct { uint32_t
		wcb_any_pbuf            :0-0 +1,
		wcb_hst_data_buf_cnt    :7-1 +1,
		wcb_sid_data_buf_cnt    :14-8 +1,
		wcb_hst_rd_ptr_buf_full :15-15 +1,
		wcb_sid_rd_ptr_buf_full :16-16 +1,
		wcb_hst_req_fifo_full   :17-17 +1,
		wcb_sid_req_fifo_full   :18-18 +1,
		wcb_hst_req_obuf_full   :19-19 +1,
		wcb_sid_req_obuf_full   :20-20 +1,
		wcb_hst_data_obuf_full  :21-21 +1,
		wcb_sid_data_obuf_full  :22-22 +1,
		ret_buf_full            :23-23 +1,
		xpb_clk_busy_bits       :31-24 +1;
	};
};

union mc_xpb_rtr_dest_map0 {
	uint32_t mc_xpb_rtr_dest_map0;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_dest_map1 {
	uint32_t mc_xpb_rtr_dest_map1;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_dest_map2 {
	uint32_t mc_xpb_rtr_dest_map2;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_dest_map3 {
	uint32_t mc_xpb_rtr_dest_map3;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_dest_map4 {
	uint32_t mc_xpb_rtr_dest_map4;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_dest_map5 {
	uint32_t mc_xpb_rtr_dest_map5;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_dest_map6 {
	uint32_t mc_xpb_rtr_dest_map6;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_dest_map7 {
	uint32_t mc_xpb_rtr_dest_map7;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_dest_map8 {
	uint32_t mc_xpb_rtr_dest_map8;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_dest_map9 {
	uint32_t mc_xpb_rtr_dest_map9;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_rtr_src_aprtr0 {
	uint32_t mc_xpb_rtr_src_aprtr0;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_rtr_src_aprtr1 {
	uint32_t mc_xpb_rtr_src_aprtr1;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_rtr_src_aprtr2 {
	uint32_t mc_xpb_rtr_src_aprtr2;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_rtr_src_aprtr3 {
	uint32_t mc_xpb_rtr_src_aprtr3;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_rtr_src_aprtr4 {
	uint32_t mc_xpb_rtr_src_aprtr4;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_rtr_src_aprtr5 {
	uint32_t mc_xpb_rtr_src_aprtr5;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_rtr_src_aprtr6 {
	uint32_t mc_xpb_rtr_src_aprtr6;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_rtr_src_aprtr7 {
	uint32_t mc_xpb_rtr_src_aprtr7;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_rtr_src_aprtr8 {
	uint32_t mc_xpb_rtr_src_aprtr8;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_rtr_src_aprtr9 {
	uint32_t mc_xpb_rtr_src_aprtr9;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_sticky {
	uint32_t mc_xpb_sticky;
	struct { uint32_t
		bits   :31-0 +1;
	};
};

union mc_xpb_sticky_w1c {
	uint32_t mc_xpb_sticky_w1c;
	struct { uint32_t
		bits   :31-0 +1;
	};
};

union mc_xpb_sub_ctrl {
	uint32_t mc_xpb_sub_ctrl;
	struct { uint32_t
		wrreq_bypass_xpb       :0-0 +1,
		stall_cns_rtr_req      :1-1 +1,
		stall_rtr_rpb_wrreq    :2-2 +1,
		stall_rtr_map_req      :3-3 +1,
		stall_map_wcb_req      :4-4 +1,
		stall_wcb_sid_req      :5-5 +1,
		stall_mc_xsp_req_send  :6-6 +1,
		stall_wcb_hst_req      :7-7 +1,
		stall_hst_hop_req      :8-8 +1,
		stall_xpb_rpb_req_attr :9-9 +1,
		reset_cns              :10-10 +1,
		reset_rtr              :11-11 +1,
		reset_ret              :12-12 +1,
		reset_map              :13-13 +1,
		reset_wcb              :14-14 +1,
		reset_hst              :15-15 +1,
		reset_hop              :16-16 +1,
		reset_sid              :17-17 +1,
		reset_srb              :18-18 +1,
		reset_cgr              :19-19 +1,
		rsvd0                  :31-20 +1;
	};
};

union mc_xpb_unc_thresh_hst {
	uint32_t mc_xpb_unc_thresh_hst;
	struct { uint32_t
		change_pref :5-0 +1,
		strong_pref :11-6 +1,
		use_unfull  :17-12 +1,
		rsvd0       :31-18 +1;
	};
};

union mc_xpb_unc_thresh_sid {
	uint32_t mc_xpb_unc_thresh_sid;
	struct { uint32_t
		change_pref :5-0 +1,
		strong_pref :11-6 +1,
		use_unfull  :17-12 +1,
		rsvd0       :31-18 +1;
	};
};

union mc_xpb_wcb_cfg {
	uint32_t mc_xpb_wcb_cfg;
	struct { uint32_t
		timeout :15-0 +1,
		hst_max :17-16 +1,
		sid_max :19-18 +1,
		rsvd0   :31-20 +1;
	};
};

union mc_xpb_wcb_sts {
	uint32_t mc_xpb_wcb_sts;
	struct { uint32_t
		pbuf_vld             :15-0 +1,
		wcb_hst_data_buf_cnt :22-16 +1,
		wcb_sid_data_buf_cnt :29-23 +1,
		rsvd0                :31-30 +1;
	};
};

union mc_xpb_xdma_peer_sys_bar0 {
	uint32_t mc_xpb_xdma_peer_sys_bar0;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_xdma_peer_sys_bar1 {
	uint32_t mc_xpb_xdma_peer_sys_bar1;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_xdma_peer_sys_bar2 {
	uint32_t mc_xpb_xdma_peer_sys_bar2;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_xdma_peer_sys_bar3 {
	uint32_t mc_xpb_xdma_peer_sys_bar3;
	struct { uint32_t
		valid   :0-0 +1,
		side_ok :1-1 +1,
		addr    :26-2 +1,
		rsvd0   :31-27 +1;
	};
};

union mc_xpb_xdma_rtr_dest_map0 {
	uint32_t mc_xpb_xdma_rtr_dest_map0;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_xdma_rtr_dest_map1 {
	uint32_t mc_xpb_xdma_rtr_dest_map1;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_xdma_rtr_dest_map2 {
	uint32_t mc_xpb_xdma_rtr_dest_map2;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_xdma_rtr_dest_map3 {
	uint32_t mc_xpb_xdma_rtr_dest_map3;
	struct { uint32_t
		nmr          :0-0 +1,
		dest_offset  :19-1 +1,
		dest_sel     :23-20 +1,
		dest_sel_rpb :24-24 +1,
		side_ok      :25-25 +1,
		aprtr_size   :30-26 +1,
		rsvd0        :31-31 +1;
	};
};

union mc_xpb_xdma_rtr_src_aprtr0 {
	uint32_t mc_xpb_xdma_rtr_src_aprtr0;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_xdma_rtr_src_aprtr1 {
	uint32_t mc_xpb_xdma_rtr_src_aprtr1;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_xdma_rtr_src_aprtr2 {
	uint32_t mc_xpb_xdma_rtr_src_aprtr2;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mc_xpb_xdma_rtr_src_aprtr3 {
	uint32_t mc_xpb_xdma_rtr_src_aprtr3;
	struct { uint32_t
		base_addr :24-0 +1,
		rsvd0     :31-25 +1;
	};
};

union mpll_ad_func_cntl {
	uint32_t mpll_ad_func_cntl;
	struct { uint32_t
		yclk_post_div :2-0 +1,
		spare         :31-3 +1;
	};
};

union mpll_ad_status {
	uint32_t mpll_ad_status;
	struct { uint32_t
		vctrladc           :2-0 +1,
		rsvd0              :3-3 +1,
		test_fbdiv_frac    :6-4 +1,
		test_fbdiv_int     :16-7 +1,
		oint_reset         :17-17 +1,
		freq_lock          :18-18 +1,
		freq_unlock_sticky :19-19 +1,
		rsvd1              :31-20 +1;
	};
};

union mpll_cntl_mode {
	uint32_t mpll_cntl_mode;
	struct { uint32_t
		instr_delay         :7-0 +1,
		mpll_sw_dir_control :8-8 +1,
		rsvd0               :10-9 +1,
		mpll_mclk_sel       :11-11 +1,
		spare_1             :12-12 +1,
		qdr                 :13-13 +1,
		mpll_ctlreq         :14-14 +1,
		rsvd1               :15-15 +1,
		mpll_chg_status     :16-16 +1,
		force_testmode      :17-17 +1,
		rsvd2               :19-18 +1,
		fast_lock_en        :20-20 +1,
		fast_lock_cntrl     :22-21 +1,
		spare_2             :23-23 +1,
		ss_ssen             :25-24 +1,
		ss_dsmode_en        :26-26 +1,
		vtoi_bias_cntrl     :27-27 +1,
		spare_3             :30-28 +1,
		global_mpll_reset   :31-31 +1;
	};
};

union mpll_control {
	uint32_t mpll_control;
	struct { uint32_t
		gddr_pwron       :0-0 +1,
		refclk_pwron     :1-1 +1,
		pll_buf_pwron_tx :2-2 +1,
		rsvd0            :11-3 +1,
		ad_bg_pwron      :12-12 +1,
		ad_pll_pwron     :13-13 +1,
		ad_pll_reset     :14-14 +1,
		spare_ad_0       :15-15 +1,
		dq_0_0_bg_pwron  :16-16 +1,
		dq_0_0_pll_pwron :17-17 +1,
		dq_0_0_pll_reset :18-18 +1,
		spare_dq_0_0     :19-19 +1,
		dq_0_1_bg_pwron  :20-20 +1,
		dq_0_1_pll_pwron :21-21 +1,
		dq_0_1_pll_reset :22-22 +1,
		spare_dq_0_1     :23-23 +1,
		dq_1_0_bg_pwron  :24-24 +1,
		dq_1_0_pll_pwron :25-25 +1,
		dq_1_0_pll_reset :26-26 +1,
		spare_dq_1_0     :27-27 +1,
		dq_1_1_bg_pwron  :28-28 +1,
		dq_1_1_pll_pwron :29-29 +1,
		dq_1_1_pll_reset :30-30 +1,
		spare_dq_1_1     :31-31 +1;
	};
};

union mpll_dq_0_0_status {
	uint32_t mpll_dq_0_0_status;
	struct { uint32_t
		vctrladc           :2-0 +1,
		rsvd0              :3-3 +1,
		test_fbdiv_frac    :6-4 +1,
		test_fbdiv_int     :16-7 +1,
		oint_reset         :17-17 +1,
		freq_lock          :18-18 +1,
		freq_unlock_sticky :19-19 +1,
		rsvd1              :31-20 +1;
	};
};

union mpll_dq_0_1_status {
	uint32_t mpll_dq_0_1_status;
	struct { uint32_t
		vctrladc           :2-0 +1,
		rsvd0              :3-3 +1,
		test_fbdiv_frac    :6-4 +1,
		test_fbdiv_int     :16-7 +1,
		oint_reset         :17-17 +1,
		freq_lock          :18-18 +1,
		freq_unlock_sticky :19-19 +1,
		rsvd1              :31-20 +1;
	};
};

union mpll_dq_1_0_status {
	uint32_t mpll_dq_1_0_status;
	struct { uint32_t
		vctrladc           :2-0 +1,
		rsvd0              :3-3 +1,
		test_fbdiv_frac    :6-4 +1,
		test_fbdiv_int     :16-7 +1,
		oint_reset         :17-17 +1,
		freq_lock          :18-18 +1,
		freq_unlock_sticky :19-19 +1,
		rsvd1              :31-20 +1;
	};
};

union mpll_dq_1_1_status {
	uint32_t mpll_dq_1_1_status;
	struct { uint32_t
		vctrladc           :2-0 +1,
		rsvd0              :3-3 +1,
		test_fbdiv_frac    :6-4 +1,
		test_fbdiv_int     :16-7 +1,
		oint_reset         :17-17 +1,
		freq_lock          :18-18 +1,
		freq_unlock_sticky :19-19 +1,
		rsvd1              :31-20 +1;
	};
};

union mpll_dq_func_cntl {
	uint32_t mpll_dq_func_cntl;
	struct { uint32_t
		yclk_post_div :2-0 +1,
		spare_0       :3-3 +1,
		yclk_sel      :4-4 +1,
		spare         :31-5 +1;
	};
};

union mpll_func_cntl_1 {
	uint32_t mpll_func_cntl_1;
	struct { uint32_t
		vco_mode :1-0 +1,
		spare_0  :3-2 +1,
		clkfrac  :15-4 +1,
		clkf     :27-16 +1,
		spare_1  :31-28 +1;
	};
};

union mpll_func_cntl_2 {
	uint32_t mpll_func_cntl_2;
	struct { uint32_t
		vctrladc_en            :0-0 +1,
		test_vctl_en           :1-1 +1,
		reset_en               :2-2 +1,
		test_bypclk_en         :3-3 +1,
		test_bypclk_src        :4-4 +1,
		test_fbdiv_frac_bypass :5-5 +1,
		test_bypmclk           :6-6 +1,
		mpll_unlock_clear      :7-7 +1,
		test_vctl_cntrl        :8-8 +1,
		test_fbdiv_ssc_bypass  :9-9 +1,
		reset_timer            :11-10 +1,
		pfd_reset_cntrl        :13-12 +1,
		rsvd0                  :16-14 +1,
		backup_2               :19-17 +1,
		lf_cntrl               :26-20 +1,
		backup                 :31-27 +1;
	};
};

union mpll_func_cntl {
	uint32_t mpll_func_cntl;
	struct { uint32_t
		spare_0   :5-5 +1,
		rsvd0     :7-6 +1,
		bg_100adj :11-8 +1,
		rsvd1     :15-12 +1,
		bg_135adj :19-16 +1,
		bwctrl    :27-20 +1,
		rsvd2     :29-28 +1,
		reg_bias  :31-30 +1;
	};
};

union mpll_seq_ucode_1 {
	uint32_t mpll_seq_ucode_1;
	struct { uint32_t
		instr0 :3-0 +1,
		instr1 :7-4 +1,
		instr2 :11-8 +1,
		instr3 :15-12 +1,
		instr4 :19-16 +1,
		instr5 :23-20 +1,
		instr6 :27-24 +1,
		instr7 :31-28 +1;
	};
};

union mpll_seq_ucode_2 {
	uint32_t mpll_seq_ucode_2;
	struct { uint32_t
		instr8  :3-0 +1,
		instr9  :7-4 +1,
		instr10 :11-8 +1,
		instr11 :15-12 +1,
		instr12 :19-16 +1,
		instr13 :23-20 +1,
		instr14 :27-24 +1,
		instr15 :31-28 +1;
	};
};

union mpll_ss1 {
	uint32_t mpll_ss1;
	struct { uint32_t
		clkv   :25-0 +1,
		spare  :31-26 +1;
	};
};

union mpll_ss2 {
	uint32_t mpll_ss2;
	struct { uint32_t
		clks   :11-0 +1,
		spare  :31-12 +1;
	};
};

union mpll_time {
	uint32_t mpll_time;
	struct { uint32_t
		mpll_lock_time  :15-0 +1,
		mpll_reset_time :31-16 +1;
	};
};

union vm_context0_cntl2 {
	uint32_t vm_context0_cntl2;
	struct { uint32_t
		clear_protection_fault_status_addr                                :0-0 +1,
		enable_clear_protection_fault_status_addr_when_invalidate_context :1-1 +1,
		enable_interrupt_processing_for_subsequent_faults_per_context     :2-2 +1,
		allow_subsequent_protection_fault_status_addr_updates             :3-3 +1,
		wait_for_idle_when_invalidate                                     :4-4 +1,
		rsvd0                                                             :31-5 +1;
	};
};

union vm_context0_cntl {
	uint32_t vm_context0_cntl;
	struct { uint32_t
		enable_context                               :0-0 +1,
		page_table_depth                             :2-1 +1,
		range_protection_fault_enable_interrupt      :3-3 +1,
		range_protection_fault_enable_default        :4-4 +1,
		rsvd0                                        :5-5 +1,
		dummy_page_protection_fault_enable_interrupt :6-6 +1,
		dummy_page_protection_fault_enable_default   :7-7 +1,
		rsvd1                                        :8-8 +1,
		pde0_protection_fault_enable_interrupt       :9-9 +1,
		pde0_protection_fault_enable_default         :10-10 +1,
		pde0_protection_fault_enable_save            :11-11 +1,
		valid_protection_fault_enable_interrupt      :12-12 +1,
		valid_protection_fault_enable_default        :13-13 +1,
		valid_protection_fault_enable_save           :14-14 +1,
		read_protection_fault_enable_interrupt       :15-15 +1,
		read_protection_fault_enable_default         :16-16 +1,
		read_protection_fault_enable_save            :17-17 +1,
		write_protection_fault_enable_interrupt      :18-18 +1,
		write_protection_fault_enable_default        :19-19 +1,
		write_protection_fault_enable_save           :20-20 +1,
		privileged_protection_fault_enable_interrupt :21-21 +1,
		privileged_protection_fault_enable_default   :22-22 +1,
		privileged_protection_fault_enable_save      :23-23 +1,
		page_table_block_size                        :27-24 +1,
		rsvd2                                        :31-28 +1;
	};
};

union vm_context0_page_table_base_addr {
	uint32_t vm_context0_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context0_page_table_end_addr {
	uint32_t vm_context0_page_table_end_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_context0_page_table_start_addr {
	uint32_t vm_context0_page_table_start_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_context0_protection_fault_addr {
	uint32_t vm_context0_protection_fault_addr;
	struct { uint32_t
		logical_page_addr :27-0 +1,
		rsvd0             :31-28 +1;
	};
};

union vm_context0_protection_fault_default_addr {
	uint32_t vm_context0_protection_fault_default_addr;
	struct { uint32_t
		physical_page_addr :27-0 +1,
		rsvd0              :31-28 +1;
	};
};

union vm_context0_protection_fault_status {
	uint32_t vm_context0_protection_fault_status;
	struct { uint32_t
		protections      :7-0 +1,
		rsvd0            :11-8 +1,
		memory_client_id :19-12 +1,
		rsvd1            :23-20 +1,
		memory_client_rw :24-24 +1,
		vmid             :28-25 +1,
		rsvd2            :31-29 +1;
	};
};

union vm_context10_page_table_base_addr {
	uint32_t vm_context10_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context11_page_table_base_addr {
	uint32_t vm_context11_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context12_page_table_base_addr {
	uint32_t vm_context12_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context13_page_table_base_addr {
	uint32_t vm_context13_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context14_page_table_base_addr {
	uint32_t vm_context14_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context15_page_table_base_addr {
	uint32_t vm_context15_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context1_cntl2 {
	uint32_t vm_context1_cntl2;
	struct { uint32_t
		clear_protection_fault_status_addr                                :0-0 +1,
		enable_clear_protection_fault_status_addr_when_invalidate_context :1-1 +1,
		enable_interrupt_processing_for_subsequent_faults_per_context     :2-2 +1,
		allow_subsequent_protection_fault_status_addr_updates             :3-3 +1,
		wait_for_idle_when_invalidate                                     :4-4 +1,
		rsvd0                                                             :31-5 +1;
	};
};

union vm_context1_cntl {
	uint32_t vm_context1_cntl;
	struct { uint32_t
		enable_context                               :0-0 +1,
		page_table_depth                             :2-1 +1,
		range_protection_fault_enable_interrupt      :3-3 +1,
		range_protection_fault_enable_default        :4-4 +1,
		rsvd0                                        :5-5 +1,
		dummy_page_protection_fault_enable_interrupt :6-6 +1,
		dummy_page_protection_fault_enable_default   :7-7 +1,
		rsvd1                                        :8-8 +1,
		pde0_protection_fault_enable_interrupt       :9-9 +1,
		pde0_protection_fault_enable_default         :10-10 +1,
		pde0_protection_fault_enable_save            :11-11 +1,
		valid_protection_fault_enable_interrupt      :12-12 +1,
		valid_protection_fault_enable_default        :13-13 +1,
		valid_protection_fault_enable_save           :14-14 +1,
		read_protection_fault_enable_interrupt       :15-15 +1,
		read_protection_fault_enable_default         :16-16 +1,
		read_protection_fault_enable_save            :17-17 +1,
		write_protection_fault_enable_interrupt      :18-18 +1,
		write_protection_fault_enable_default        :19-19 +1,
		write_protection_fault_enable_save           :20-20 +1,
		privileged_protection_fault_enable_interrupt :21-21 +1,
		privileged_protection_fault_enable_default   :22-22 +1,
		privileged_protection_fault_enable_save      :23-23 +1,
		page_table_block_size                        :27-24 +1,
		rsvd2                                        :31-28 +1;
	};
};

union vm_context1_page_table_base_addr {
	uint32_t vm_context1_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context1_page_table_end_addr {
	uint32_t vm_context1_page_table_end_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_context1_page_table_start_addr {
	uint32_t vm_context1_page_table_start_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_context1_protection_fault_addr {
	uint32_t vm_context1_protection_fault_addr;
	struct { uint32_t
		logical_page_addr :27-0 +1,
		rsvd0             :31-28 +1;
	};
};

union vm_context1_protection_fault_default_addr {
	uint32_t vm_context1_protection_fault_default_addr;
	struct { uint32_t
		physical_page_addr :27-0 +1,
		rsvd0              :31-28 +1;
	};
};

union vm_context1_protection_fault_status {
	uint32_t vm_context1_protection_fault_status;
	struct { uint32_t
		protections      :7-0 +1,
		rsvd0            :11-8 +1,
		memory_client_id :19-12 +1,
		rsvd1            :23-20 +1,
		memory_client_rw :24-24 +1,
		vmid             :28-25 +1,
		rsvd2            :31-29 +1;
	};
};

union vm_context2_page_table_base_addr {
	uint32_t vm_context2_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context3_page_table_base_addr {
	uint32_t vm_context3_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context4_page_table_base_addr {
	uint32_t vm_context4_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context5_page_table_base_addr {
	uint32_t vm_context5_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context6_page_table_base_addr {
	uint32_t vm_context6_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context7_page_table_base_addr {
	uint32_t vm_context7_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context8_page_table_base_addr {
	uint32_t vm_context8_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_context9_page_table_base_addr {
	uint32_t vm_context9_page_table_base_addr;
	struct { uint32_t
		physical_page_number :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_contexts_disable {
	uint32_t vm_contexts_disable;
	struct { uint32_t
		disable_context_0  :0-0 +1,
		disable_context_1  :1-1 +1,
		disable_context_2  :2-2 +1,
		disable_context_3  :3-3 +1,
		disable_context_4  :4-4 +1,
		disable_context_5  :5-5 +1,
		disable_context_6  :6-6 +1,
		disable_context_7  :7-7 +1,
		disable_context_8  :8-8 +1,
		disable_context_9  :9-9 +1,
		disable_context_10 :10-10 +1,
		disable_context_11 :11-11 +1,
		disable_context_12 :12-12 +1,
		disable_context_13 :13-13 +1,
		disable_context_14 :14-14 +1,
		disable_context_15 :15-15 +1,
		rsvd0              :31-16 +1;
	};
};

union vm_debug {
	uint32_t vm_debug;
	struct { uint32_t
		flags  :31-0 +1;
	};
};

union vm_dummy_page_fault_addr {
	uint32_t vm_dummy_page_fault_addr;
	struct { uint32_t
		dummy_page_addr :27-0 +1,
		rsvd0           :31-28 +1;
	};
};

union vm_dummy_page_fault_cntl {
	uint32_t vm_dummy_page_fault_cntl;
	struct { uint32_t
		dummy_page_fault_enable    :0-0 +1,
		dummy_page_address_logical :1-1 +1,
		dummy_page_compare_mask    :3-2 +1,
		rsvd0                      :31-4 +1;
	};
};

union vm_fault_client_id {
	uint32_t vm_fault_client_id;
	struct { uint32_t
		memory_client      :8-0 +1,
		memory_client_mask :17-9 +1,
		rsvd0              :31-18 +1;
	};
};

union vm_invalidate_request {
	uint32_t vm_invalidate_request;
	struct { uint32_t
		invalidate_domain_0  :0-0 +1,
		invalidate_domain_1  :1-1 +1,
		invalidate_domain_2  :2-2 +1,
		invalidate_domain_3  :3-3 +1,
		invalidate_domain_4  :4-4 +1,
		invalidate_domain_5  :5-5 +1,
		invalidate_domain_6  :6-6 +1,
		invalidate_domain_7  :7-7 +1,
		invalidate_domain_8  :8-8 +1,
		invalidate_domain_9  :9-9 +1,
		invalidate_domain_10 :10-10 +1,
		invalidate_domain_11 :11-11 +1,
		invalidate_domain_12 :12-12 +1,
		invalidate_domain_13 :13-13 +1,
		invalidate_domain_14 :14-14 +1,
		invalidate_domain_15 :15-15 +1,
		rsvd0                :31-16 +1;
	};
};

union vm_invalidate_response {
	uint32_t vm_invalidate_response;
	struct { uint32_t
		domain_invalidated_0  :0-0 +1,
		domain_invalidated_1  :1-1 +1,
		domain_invalidated_2  :2-2 +1,
		domain_invalidated_3  :3-3 +1,
		domain_invalidated_4  :4-4 +1,
		domain_invalidated_5  :5-5 +1,
		domain_invalidated_6  :6-6 +1,
		domain_invalidated_7  :7-7 +1,
		domain_invalidated_8  :8-8 +1,
		domain_invalidated_9  :9-9 +1,
		domain_invalidated_10 :10-10 +1,
		domain_invalidated_11 :11-11 +1,
		domain_invalidated_12 :12-12 +1,
		domain_invalidated_13 :13-13 +1,
		domain_invalidated_14 :14-14 +1,
		domain_invalidated_15 :15-15 +1,
		rsvd0                 :31-16 +1;
	};
};

union vm_l2_bank_select_maska {
	uint32_t vm_l2_bank_select_maska;
	struct { uint32_t
		bank_select_mask :27-0 +1,
		rsvd0            :31-28 +1;
	};
};

union vm_l2_bank_select_maskb {
	uint32_t vm_l2_bank_select_maskb;
	struct { uint32_t
		bank_select_mask :7-0 +1,
		rsvd0            :31-8 +1;
	};
};

union vm_l2_cg {
	uint32_t vm_l2_cg;
	struct { uint32_t
		offdly        :11-6 +1,
		rsvd0         :17-12 +1,
		enable        :18-18 +1,
		mem_ls_enable :19-19 +1,
		rsvd1         :31-20 +1;
	};
};

union vm_l2_cntl2 {
	uint32_t vm_l2_cntl2;
	struct { uint32_t
		invalidate_all_l1_tlbs          :0-0 +1,
		invalidate_l2_cache             :1-1 +1,
		rsvd0                           :20-2 +1,
		disable_invalidate_per_domain   :21-21 +1,
		disable_bigk_cache_optimization :22-22 +1,
		l2_cache_bigk_vmid_mode         :25-23 +1,
		invalidate_cache_mode           :27-26 +1,
		rsvd1                           :31-28 +1;
	};
};

union vm_l2_cntl3 {
	uint32_t vm_l2_cntl3;
	struct { uint32_t
		bank_select                              :5-0 +1,
		l2_cache_update_mode                     :7-6 +1,
		l2_cache_update_wildcard_reference_value :12-8 +1,
		rsvd0                                    :14-13 +1,
		l2_cache_bigk_fragment_size              :19-15 +1,
		l2_cache_bigk_associativity              :20-20 +1,
		l2_cache_4k_effective_size               :23-21 +1,
		l2_cache_bigk_effective_size             :27-24 +1,
		l2_cache_4k_force_miss                   :28-28 +1,
		l2_cache_bigk_force_miss                 :29-29 +1,
		rsvd1                                    :31-30 +1;
	};
};

union vm_l2_cntl {
	uint32_t vm_l2_cntl;
	struct { uint32_t
		enable_l2_cache                          :0-0 +1,
		enable_l2_fragment_processing            :1-1 +1,
		l2_cache_pte_endian_swap_mode            :3-2 +1,
		l2_cache_pde_endian_swap_mode            :5-4 +1,
		rsvd0                                    :7-6 +1,
		l2_pde0_cache_tag_generation_mode        :8-8 +1,
		enable_l2_pte_cache_lru_update_by_write  :9-9 +1,
		enable_l2_pde0_cache_lru_update_by_write :10-10 +1,
		rsvd1                                    :11-11 +1,
		l2_pde0_cache_split_mode                 :14-12 +1,
		effective_l2_queue_size                  :17-15 +1,
		pde_fault_classification                 :18-18 +1,
		context1_identity_access_mode            :20-19 +1,
		identity_mode_fragment_size              :25-21 +1,
		l2_cache_4k_swap_tag_index_lsbs          :27-26 +1,
		l2_cache_bigk_swap_tag_index_lsbs        :30-28 +1,
		rsvd2                                    :31-31 +1;
	};
};

union vm_l2_context1_identity_aperture_high_addr {
	uint32_t vm_l2_context1_identity_aperture_high_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_l2_context1_identity_aperture_low_addr {
	uint32_t vm_l2_context1_identity_aperture_low_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_l2_context_identity_physical_offset {
	uint32_t vm_l2_context_identity_physical_offset;
	struct { uint32_t
		physical_page_offset :27-0 +1,
		rsvd0                :31-28 +1;
	};
};

union vm_l2_status {
	uint32_t vm_l2_status;
	struct { uint32_t
		l2_busy             :0-0 +1,
		context_domain_busy :16-1 +1,
		rsvd0               :31-17 +1;
	};
};

union vm_prt_aperture0_high_addr {
	uint32_t vm_prt_aperture0_high_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_prt_aperture0_low_addr {
	uint32_t vm_prt_aperture0_low_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_prt_aperture1_high_addr {
	uint32_t vm_prt_aperture1_high_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_prt_aperture1_low_addr {
	uint32_t vm_prt_aperture1_low_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_prt_aperture2_high_addr {
	uint32_t vm_prt_aperture2_high_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_prt_aperture2_low_addr {
	uint32_t vm_prt_aperture2_low_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_prt_aperture3_high_addr {
	uint32_t vm_prt_aperture3_high_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_prt_aperture3_low_addr {
	uint32_t vm_prt_aperture3_low_addr;
	struct { uint32_t
		logical_page_number :27-0 +1,
		rsvd0               :31-28 +1;
	};
};

union vm_prt_cntl {
	uint32_t vm_prt_cntl;
	struct { uint32_t
		cb_disable_fault_on_unmapped_access :0-0 +1,
		tc_disable_fault_on_unmapped_access :1-1 +1,
		l2_cache_store_invalid_entries      :2-2 +1,
		l1_tlb_store_invalid_entries        :3-3 +1,
		rsvd0                               :31-4 +1;
	};
};
