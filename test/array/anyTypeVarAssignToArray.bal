// RUN: JAVA_HOME=%java_path %testRunScript %s %nballerinacc | filecheck %s

public function print_str(string val) = external;

public function printu32(int val) = external;

public function main() {
    int[] a = [5];
    any x = 2;
    a[0] = <int>x;
    print_str("RESULT=");
    printu32(a[0]);
}

// CHECK: RESULT=2
