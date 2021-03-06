; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt -S -loop-reduce < %s | FileCheck %s

target datalayout = "e-p:64:64:64-n32:64"

define void @test1(ptr %p.start, i64 %len) {
; CHECK-LABEL: @test1(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[UGLYGEP:%.*]] = getelementptr i8, ptr [[P_START:%.*]], i64 4
; CHECK-NEXT:    br label [[LOOP:%.*]]
; CHECK:       loop:
; CHECK-NEXT:    [[LSR_IV1:%.*]] = phi ptr [ [[UGLYGEP2:%.*]], [[LOOP]] ], [ [[UGLYGEP]], [[ENTRY:%.*]] ]
; CHECK-NEXT:    [[LSR_IV:%.*]] = phi i64 [ [[LSR_IV_NEXT:%.*]], [[LOOP]] ], [ [[LEN:%.*]], [[ENTRY]] ]
; CHECK-NEXT:    [[TMP0:%.*]] = load volatile i32, ptr [[LSR_IV1]], align 4
; CHECK-NEXT:    [[LSR_IV_NEXT]] = add i64 [[LSR_IV]], -1
; CHECK-NEXT:    [[UGLYGEP2]] = getelementptr i8, ptr [[LSR_IV1]], i64 4
; CHECK-NEXT:    [[C:%.*]] = icmp ne i64 [[LSR_IV_NEXT]], 0
; CHECK-NEXT:    br i1 [[C]], label [[LOOP]], label [[EXIT:%.*]]
; CHECK:       exit:
; CHECK-NEXT:    ret void
;
entry:
  br label %loop

loop:
  %i = phi i64 [ 0, %entry ], [ %i.next, %loop ]
  %p = phi ptr [ %p.start, %entry ], [ %p.next, %loop ]
  %i.next = add nuw i64 %i, 1
  %p.next = getelementptr i32, ptr %p, i64 1
  load volatile i32, ptr %p.next
  %c = icmp ne i64 %i.next, %len
  br i1 %c, label %loop, label %exit

exit:
  ret void
}
