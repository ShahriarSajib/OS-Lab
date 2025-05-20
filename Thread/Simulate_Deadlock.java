class DeadlockRunnable {
    static final Object Lock1 = new Object();
    static final Object Lock2 = new Object();

    public static void main(String[] args) {
        Runnable r1 = () -> {
            synchronized (Lock1) {
                System.out.println("Thread 1: Holding Lock1...");
                try { Thread.sleep(100); } catch (Exception e) {}
                System.out.println("Thread 1: Waiting for Lock2...");
                synchronized (Lock2) {
                    System.out.println("Thread 1: Acquired Lock2!");
                }
            }
        };

        Runnable r2 = () -> {
            synchronized (Lock2) {
                System.out.println("Thread 2: Holding Lock2...");
                try { Thread.sleep(100); } catch (Exception e) {}
                System.out.println("Thread 2: Waiting for Lock1...");
                synchronized (Lock1) {
                    System.out.println("Thread 2: Acquired Lock1!");
                }
            }
        };

        Thread t1 = new Thread(r1);
        Thread t2 = new Thread(r2);

        t1.start();
        t2.start();
    }
}
