class TaskData {
    String name;
    int repeat;

    TaskData(String name, int repeat) {
        this.name = name;
        this.repeat = repeat;
    }
}

class BlockParamRunnable implements Runnable {
    private final TaskData task;

    public BlockParamRunnable(TaskData task) {
        this.task = task;
    }

    public void run() {
        for (int i = 0; i < task.repeat; i++) {
            System.out.println(task.name + " - Step " + (i + 1));
        }
    }

    public static void main(String[] args) {
        TaskData task1 = new TaskData("AlphaTask", 2);
        TaskData task2 = new TaskData("BetaTask", 3);

        Thread t1 = new Thread(new BlockParamRunnable(task1));
        Thread t2 = new Thread(new BlockParamRunnable(task2));

        t1.start();
        t2.start();
    }
}
