; ModuleID = 'devirt_module'
source_filename = "devirt_module"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(readwrite, inaccessiblemem: none)
define void @devirtualized() local_unnamed_addr #0 {
entry:
  %vstack_memory = alloca [2048 x i8], align 1
  %vsp_inc6413 = getelementptr i8, ptr %vstack_memory, i64 2160
  %vsp_inc6414 = getelementptr i8, ptr %vstack_memory, i64 2168
  %vsp_dec64 = getelementptr i8, ptr %vstack_memory, i64 2176
  %0 = ptrtoint ptr %vsp_dec64 to i64
  %sub_64_result = add i64 %0, -16
  store i64 %sub_64_result, ptr %vsp_inc6414, align 4
  %zf = icmp eq i64 %sub_64_result, 0
  %zf_ext = sext i1 %zf to i64
  store i64 %zf_ext, ptr %vsp_inc6413, align 4
  %1 = inttoptr i64 %sub_64_result to ptr
  %vsp_dec6427 = getelementptr i8, ptr %1, i64 -8
  %vsp_dec6428 = getelementptr i8, ptr %1, i64 -16
  %vsp_dec6429 = getelementptr i8, ptr %1, i64 -24
  %add_64_result39 = add i64 %0, 16
  %vsp_dec6446 = getelementptr i8, ptr %1, i64 -12
  %2 = inttoptr i64 %add_64_result39 to ptr
  %add_64_result61 = add i64 %0, -8
  %zf63 = icmp eq i64 %add_64_result61, 0
  %zf_ext64 = sext i1 %zf63 to i64
  %3 = inttoptr i64 %add_64_result61 to ptr
  store i32 1998950979, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %4 = load i32, ptr %3, align 4
  %or_32_result = or i32 %4, 35
  store i32 %or_32_result, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %5 = load i32, ptr %3, align 4
  %and_32_result = and i32 %5, 35
  store i32 %and_32_result, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %6 = load i32, ptr %3, align 4
  %add_32_result = add i32 %6, 2115
  store i32 %add_32_result, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %7 = load i32, ptr %3, align 4
  %and_32_result208 = and i32 %7, 21606
  store i32 %and_32_result208, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %8 = load i32, ptr %3, align 4
  %add_32_result245 = add i32 %8, 2115
  store i32 %add_32_result245, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %9 = load i32, ptr %3, align 4
  %or_32_result282 = or i32 %9, 564
  store i32 %or_32_result282, ptr %3, align 4
  %add_64_result304 = add i64 %0, -4
  %10 = inttoptr i64 %add_64_result304 to ptr
  store i32 0, ptr %10, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %11 = load i32, ptr %3, align 4
  %add_32_result343 = add i32 %11, 407124
  store i32 %add_32_result343, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %12 = load i32, ptr %3, align 4
  %and_32_result380 = and i32 %12, 17733
  store i32 %and_32_result380, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %13 = load i32, ptr %3, align 4
  %or_32_result417 = or i32 %13, 414822
  store i32 %or_32_result417, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %14 = load i32, ptr %3, align 4
  %sub_32_result = add i32 %14, -21044
  store i32 %sub_32_result, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %15 = load i32, ptr %3, align 4
  %sub_32_result490 = add i32 %15, -2147
  store i32 %sub_32_result490, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %16 = load i32, ptr %3, align 4
  %xor_32_result = xor i32 %16, 7
  store i32 %xor_32_result, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result39, ptr %vsp_dec6427, align 4
  store i64 %add_64_result39, ptr %vsp_dec6428, align 4
  %17 = load i32, ptr %2, align 4
  %zf565 = icmp eq i32 %17, 1859
  %zf_ext566 = sext i1 %zf565 to i64
  store i64 %zf_ext566, ptr %vsp_dec6446, align 4
  store i64 %zf_ext566, ptr %vsp_dec6427, align 4
  br i1 %zf565, label %entry.WRITE32_278_crit_edge, label %WRITE32_278

entry.WRITE32_278_crit_edge:                      ; preds = %entry
  %.pre = load i64, ptr %vsp_dec6446, align 4
  %.pre1851 = inttoptr i64 %.pre to ptr
  br label %WRITE32_278

WRITE32_278:                                      ; preds = %entry, %entry.WRITE32_278_crit_edge
  %.pre-phi = phi ptr [ %.pre1851, %entry.WRITE32_278_crit_edge ], [ %10, %entry ]
  %18 = phi i32 [ -1, %entry.WRITE32_278_crit_edge ], [ 1, %entry ]
  store i32 %18, ptr %.pre-phi, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %19 = load i32, ptr %3, align 4
  %add_32_result624 = add i32 %19, 414563
  store i32 %add_32_result624, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %20 = load i32, ptr %3, align 4
  %and_32_result661 = and i32 %20, 480340
  store i32 %and_32_result661, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %21 = load i32, ptr %3, align 4
  %or_32_result698 = or i32 %21, 1876
  store i32 %or_32_result698, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %22 = load i32, ptr %3, align 4
  %add_32_result735 = add i32 %22, 1
  store i32 %add_32_result735, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %23 = load i32, ptr %3, align 4
  %sub_32_result772 = add i32 %23, -1
  store i32 %sub_32_result772, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %24 = load i32, ptr %3, align 4
  %add_32_result809 = add i32 %24, 1809
  store i32 %add_32_result809, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result39, ptr %vsp_dec6427, align 4
  store i64 %add_64_result39, ptr %vsp_dec6428, align 4
  %25 = load i32, ptr %2, align 4
  %zf848 = icmp eq i32 %25, 2418
  %zf_ext849 = sext i1 %zf848 to i64
  store i64 %zf_ext849, ptr %vsp_dec6446, align 4
  store i64 %zf_ext849, ptr %vsp_dec6427, align 4
  br i1 %zf848, label %WRITE32_278.WRITE32_402_crit_edge, label %WRITE32_402

WRITE32_278.WRITE32_402_crit_edge:                ; preds = %WRITE32_278
  %.pre1847 = load i64, ptr %vsp_dec6446, align 4
  %.pre1852 = inttoptr i64 %.pre1847 to ptr
  br label %WRITE32_402

WRITE32_402:                                      ; preds = %WRITE32_278, %WRITE32_278.WRITE32_402_crit_edge
  %.pre-phi1853 = phi ptr [ %.pre1852, %WRITE32_278.WRITE32_402_crit_edge ], [ %10, %WRITE32_278 ]
  %26 = phi i32 [ -1, %WRITE32_278.WRITE32_402_crit_edge ], [ 1, %WRITE32_278 ]
  store i32 %26, ptr %.pre-phi1853, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %27 = load i32, ptr %3, align 4
  %add_32_result908 = add i32 %27, 13891
  store i32 %add_32_result908, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %28 = load i32, ptr %3, align 4
  %add_32_result945 = add i32 %28, 84
  store i32 %add_32_result945, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %29 = load i32, ptr %3, align 4
  %or_32_result982 = or i32 %29, 84
  store i32 %or_32_result982, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %30 = load i32, ptr %3, align 4
  %or_32_result1019 = or i32 %30, 817
  store i32 %or_32_result1019, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %31 = load i32, ptr %3, align 4
  %or_32_result1056 = or i32 %31, 18
  store i32 %or_32_result1056, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %32 = load i32, ptr %3, align 4
  %add_32_result1093 = add i32 %32, 801
  store i32 %add_32_result1093, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result39, ptr %vsp_dec6427, align 4
  store i64 %add_64_result39, ptr %vsp_dec6428, align 4
  %33 = load i32, ptr %2, align 4
  %zf1132 = icmp eq i32 %33, 1638
  %zf_ext1133 = sext i1 %zf1132 to i64
  store i64 %zf_ext1133, ptr %vsp_dec6446, align 4
  store i64 %zf_ext1133, ptr %vsp_dec6427, align 4
  br i1 %zf1132, label %WRITE32_402.WRITE32_526_crit_edge, label %WRITE32_526

WRITE32_402.WRITE32_526_crit_edge:                ; preds = %WRITE32_402
  %.pre1848 = load i64, ptr %vsp_dec6446, align 4
  %.pre1854 = inttoptr i64 %.pre1848 to ptr
  br label %WRITE32_526

WRITE32_526:                                      ; preds = %WRITE32_402, %WRITE32_402.WRITE32_526_crit_edge
  %.pre-phi1855 = phi ptr [ %.pre1854, %WRITE32_402.WRITE32_526_crit_edge ], [ %10, %WRITE32_402 ]
  %34 = phi i32 [ -1, %WRITE32_402.WRITE32_526_crit_edge ], [ 1, %WRITE32_402 ]
  store i32 %34, ptr %.pre-phi1855, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %35 = load i32, ptr %3, align 4
  %sub_32_result1192 = add i32 %35, -151
  store i32 %sub_32_result1192, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %36 = load i32, ptr %3, align 4
  %add_32_result1229 = add i32 %36, 1860
  store i32 %add_32_result1229, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %37 = load i32, ptr %3, align 4
  %or_32_result1266 = or i32 %37, 84
  store i32 %or_32_result1266, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %38 = load i32, ptr %3, align 4
  %sub_32_result1303 = add i32 %38, -130
  store i32 %sub_32_result1303, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %39 = load i32, ptr %3, align 4
  %or_32_result1340 = or i32 %39, 18
  store i32 %or_32_result1340, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %40 = load i32, ptr %3, align 4
  %add_32_result1377 = add i32 %40, 547
  store i32 %add_32_result1377, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result39, ptr %vsp_dec6427, align 4
  store i64 0, ptr %vsp_dec6428, align 4
  %41 = load i32, ptr %2, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %zf_ext64, ptr %vsp_dec6428, align 4
  %42 = load i32, ptr %3, align 4
  %zf1436 = icmp eq i32 %42, %41
  %zf_ext1437 = sext i1 %zf1436 to i64
  store i64 %zf_ext1437, ptr %vsp_dec6446, align 4
  store i64 %zf_ext1437, ptr %vsp_dec6427, align 4
  br i1 %zf1436, label %WRITE32_526.WRITE32_658_crit_edge, label %WRITE32_658

WRITE32_526.WRITE32_658_crit_edge:                ; preds = %WRITE32_526
  %.pre1849 = load i64, ptr %vsp_dec6446, align 4
  %.pre1856 = inttoptr i64 %.pre1849 to ptr
  br label %WRITE32_658

WRITE32_658:                                      ; preds = %WRITE32_526, %WRITE32_526.WRITE32_658_crit_edge
  %.pre-phi1857 = phi ptr [ %.pre1856, %WRITE32_526.WRITE32_658_crit_edge ], [ %10, %WRITE32_526 ]
  %43 = phi i32 [ -1, %WRITE32_526.WRITE32_658_crit_edge ], [ 1, %WRITE32_526 ]
  store i32 %43, ptr %.pre-phi1857, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %44 = load i32, ptr %3, align 4
  %add_32_result1496 = add i32 %44, 29506
  store i32 %add_32_result1496, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %45 = load i32, ptr %3, align 4
  %xor_32_result1533 = xor i32 %45, 66
  store i32 %xor_32_result1533, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %46 = load i32, ptr %3, align 4
  %xor_32_result1570 = xor i32 %46, 1860
  store i32 %xor_32_result1570, ptr %3, align 4
  %add_64_result1592 = add i64 %0, -12
  %zf1594 = icmp eq i64 %add_64_result1592, 0
  %zf_ext1595 = sext i1 %zf1594 to i64
  %47 = inttoptr i64 %add_64_result1592 to ptr
  store i32 29763, ptr %47, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %48 = load i32, ptr %3, align 4
  %xor_32_result1631 = xor i32 %48, 51
  store i32 %xor_32_result1631, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %49 = load i32, ptr %3, align 4
  %or_32_result1668 = or i32 %49, 136
  store i32 %or_32_result1668, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result61, ptr %vsp_dec6427, align 4
  store i64 %add_64_result61, ptr %vsp_dec6428, align 4
  %50 = load i32, ptr %3, align 4
  %add_32_result1705 = add i32 %50, 1892
  store i32 %add_32_result1705, ptr %3, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result39, ptr %vsp_dec6427, align 4
  store i64 0, ptr %vsp_dec6428, align 4
  %51 = load i32, ptr %2, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result1592, ptr %vsp_dec6427, align 4
  store i64 %zf_ext1595, ptr %vsp_dec6428, align 4
  %52 = load i32, ptr %47, align 4
  %zf1764 = icmp eq i32 %52, %51
  %zf_ext1765 = sext i1 %zf1764 to i64
  store i64 %zf_ext1765, ptr %vsp_dec6446, align 4
  store i64 %zf_ext1765, ptr %vsp_dec6427, align 4
  br i1 %zf1764, label %WRITE32_658.WRITE32_801_crit_edge, label %WRITE32_801

WRITE32_658.WRITE32_801_crit_edge:                ; preds = %WRITE32_658
  %.pre1850 = load i64, ptr %vsp_dec6446, align 4
  %.pre1858 = inttoptr i64 %.pre1850 to ptr
  br label %WRITE32_801

WRITE32_801:                                      ; preds = %WRITE32_658, %WRITE32_658.WRITE32_801_crit_edge
  %.pre-phi1859 = phi ptr [ %.pre1858, %WRITE32_658.WRITE32_801_crit_edge ], [ %10, %WRITE32_658 ]
  %53 = phi i32 [ -1, %WRITE32_658.WRITE32_801_crit_edge ], [ 1, %WRITE32_658 ]
  store i32 %53, ptr %.pre-phi1859, align 4
  store i64 0, ptr %vsp_dec6429, align 4
  store i64 %add_64_result304, ptr %vsp_dec6427, align 4
  store i64 0, ptr %vsp_dec6428, align 4
  store i64 %0, ptr %vsp_dec6427, align 4
  store i64 0, ptr %vsp_dec6428, align 4
  ret void
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(readwrite, inaccessiblemem: none) }
